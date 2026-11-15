#include "app.h"

#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"


void APP_Init(void)
{
    /* Application initialization */
    BSP_LED_Init(LED_GREEN);
}

void APP_Run(void)
{
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(500);
}
