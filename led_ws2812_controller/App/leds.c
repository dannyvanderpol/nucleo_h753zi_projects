/* Function for updating the LEDs from the buffer. */

#include "leds.h"


void LEDS_Pulse(uint32_t level);


LEDS_t LEDS_Buffer[NUM_LEDS] = {0};


void LEDS_Update(void)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        // Send data: GRB
        for (int bit = 7; bit >= 0; bit--)
        {
            LEDS_Pulse((LEDS_Buffer[i].green >> bit) & 0x01);
        }
        for (int bit = 7; bit >= 0; bit--)
        {
            LEDS_Pulse((LEDS_Buffer[i].red >> bit) & 0x01);
        }
        for (int bit = 7; bit >= 0; bit--)
        {
            LEDS_Pulse((LEDS_Buffer[i].blue >> bit) & 0x01);
        }
    }
}

void LEDS_Pulse(uint32_t level)
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


/*

Old code for walking light.

    for (int i = 0; i < NUM_LEDS; i++)
    {
        for (int j = 0; j < NUM_LEDS; j++)
        {
            if (i == j)
            {
                LedBuffer[j].green = 20;
            }
            else
            {
                LedBuffer[j].green = 0;
            }
        }
        // Trigger high
        GPIOB->BSRR = GPIO_BSRR_BS10;
        UpdateLeds();
        // Trigger low
        GPIOB->BSRR = GPIO_BSRR_BR10;
        HAL_Delay(100);
    }

*/
