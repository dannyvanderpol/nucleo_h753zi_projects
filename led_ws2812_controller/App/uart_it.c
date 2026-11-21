/*
    UART interrupt functions.
    When using the BSP, interupts for USART3 (COM port using STLINK) are not enabled.
*/

#include <stdbool.h>

#include "uart_it.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_nucleo.h"


extern UART_HandleTypeDef hcom_uart[];

static char commandBuffer[UART_IT_RX_BUFFER_SIZE];
static volatile uint8_t commandReceived = 0;
static uint8_t rxChar;
static uint8_t index = 0;


void UART_IT_Init(void)
{
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    HAL_UART_Receive_IT(&hcom_uart[COM1], &rxChar, 1);
}


bool UART_IT_CommandReceived(void)
{
    return commandReceived;
}


char* UART_IT_GetCommand(void)
{
    commandReceived = 0;
    return commandBuffer;
}


void USART3_IRQHandler(void)
{
    HAL_UART_IRQHandler(&hcom_uart[COM1]);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &hcom_uart[COM1])
    {
        if ((rxChar == '\r') || (rxChar == '\n'))
        {
            commandBuffer[index] = '\0';
            commandReceived = 1;
            index = 0;
        }
        else
        {
            commandReceived = 0;
            if (index < sizeof(commandBuffer) - 1)
            {
                commandBuffer[index++] = rxChar;
            }
            else
            {
                index = 0;
            }
        }
        HAL_UART_Receive_IT(&hcom_uart[COM1], &rxChar, 1);
    }
}
