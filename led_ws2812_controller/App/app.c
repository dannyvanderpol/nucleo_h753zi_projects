/*
Control a RGB LED.

Pin PB10: Trigger       (CN10, pin 32, output)
Pin PA0 : Data output   (CN10, pin 29, output)

*/

#include "app.h"

#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"


#define NUM_LEDS    75


void UpdateLeds(void);
void Pulse(uint32_t level);


// Struct for the LEDs
typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Led_t;

// LED buffer default to off
Led_t LedBuffer[NUM_LEDS] = {0};


void APP_Init(void)
{
    BSP_LED_On(LED_GREEN);

    /* Enable GPIOB clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    /* Configure PB10 */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Configure PA0 */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Set initial state */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

    /* Configure counter for pusle generation */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    UpdateLeds();
}

void APP_Run(void)
{
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
}


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
