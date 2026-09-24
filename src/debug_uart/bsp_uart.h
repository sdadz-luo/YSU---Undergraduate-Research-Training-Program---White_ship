#ifndef BSP_UART_H_
#define BSP_UART_H_
#include "hal_data.h"
#include "stdio.h"

void UART5_Init(void);
void uart5_callback(uart_callback_args_t *p_args);
void UART2_Init(void);
void uart2_callback(uart_callback_args_t *p_args);
void UART3_Init(void);
void uart3_callback(uart_callback_args_t *p_args);
void UART8_Init(void);
void uart8_callback(uart_callback_args_t *p_args);
void UART9_Init(void);
void uart9_callback(uart_callback_args_t *p_args);
#endif