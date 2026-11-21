/*
Control a RGB LED.

Pin PB10: Trigger       (CN10, pin 32, output)
Pin PA0 : Data output   (CN10, pin 29, output)

*/

#include <stdio.h>

#include "app.h"
#include "uart_it.h"
#include "leds.h"

#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"


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

    UART_IT_Init();

    printf("UART ready\r\n");
}


void APP_Run(void)
{
    HAL_Delay(1000);
}
