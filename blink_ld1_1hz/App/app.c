#include "app.h"

#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"


void APP_Init(void)
{
    /* No initialization needed */
}

void APP_Run(void)
{
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(500);
}
