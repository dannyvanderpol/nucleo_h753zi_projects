#include "leds.h"


void Pulse(uint32_t level);


Led_t LedBuffer[NUM_LEDS] = {0};


void UpdateLeds(void)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        // Send data: GRB
        for (int bit = 7; bit >= 0; bit--)
        {
            Pulse((LedBuffer[i].green >> bit) & 0x01);
        }
        for (int bit = 7; bit >= 0; bit--)
        {
            Pulse((LedBuffer[i].red >> bit) & 0x01);
        }
        for (int bit = 7; bit >= 0; bit--)
        {
            Pulse((LedBuffer[i].blue >> bit) & 0x01);
        }
    }
}

void Pulse(uint32_t level)
{
    // Level = 1/0 (high/low sequence)
    // Send 1: high time: 580ns to 1us
    // Send 0: high time: 220ns to 380ns
    // Followed by low time: 580ns to 1us

    // high time: 200ns  + 500ns only if level is 1
    uint32_t ticks = 55 + (level * 235);
    // Pulse PA0
    GPIOA->BSRR = GPIO_BSRR_BS0;
    // High time == ticks
    uint32_t start = DWT->CYCCNT;
    while ((DWT->CYCCNT - start) < ticks) {}
    GPIOA->BSRR = GPIO_BSRR_BR0;
    // Low time
    start = DWT->CYCCNT;
    while ((DWT->CYCCNT - start) < 270) {}
}
