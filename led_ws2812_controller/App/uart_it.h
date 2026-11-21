/* UART interrupt header file. */

#ifndef UART_IT_H
#define UART_IT_H

#include <stdbool.h>


#define UART_IT_RX_BUFFER_SIZE  64

void UART_IT_Init(void);
bool UART_IT_CommandReceived(void);
char* UART_IT_GetCommand(void);

#endif /* UART_IT_H */
