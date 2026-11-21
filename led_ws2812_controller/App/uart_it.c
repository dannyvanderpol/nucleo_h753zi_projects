/*
    UART interrupt functions.
    When using the BSP, interupts for USART3 (COM port using STLINK) are not enabled.
*/

#include <stdio.h>


#include "uart_it.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"


extern UART_HandleTypeDef hcom_uart[];

uint8_t rxChar;


void UART_IT_Init(void)
{
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    HAL_UART_Receive_IT(&hcom_uart[COM1], &rxChar, 1);
}


void USART3_IRQHandler(void)
{
    HAL_UART_IRQHandler(&hcom_uart[COM1]);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &hcom_uart[COM1])
    {
        printf("You typed: %c\r\n", rxChar);

        /* Arm the next receive */
        HAL_UART_Receive_IT(&hcom_uart[COM1], &rxChar, 1);
    }
}
