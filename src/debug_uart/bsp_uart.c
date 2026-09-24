#include  "bsp_uart.h"
#include  "stdio.h"
extern int ceshi;
/////////imu串口
void UART5_Init(void){
	fsp_err_t err=FSP_SUCCESS;
	
	err=R_SCI_UART_Open(&g_uart5_ctrl,&g_uart5_cfg);
	
	assert(FSP_SUCCESS==err);

}
fsp_err_t err=FSP_SUCCESS;
volatile bool uart_send_complete_flag = false;

void uart5_callback(uart_callback_args_t *p_args){
	
	switch(p_args -> event){
		case UART_EVENT_RX_CHAR:{

			break;
		}
		case UART_EVENT_TX_COMPLETE:{
			uart_send_complete_flag = true;
			break;
		}
		default:
			break;
	}

	
	
}
/////////lora串口
void UART2_Init(void){
	
	err=R_SCI_UART_Open(&g_uart2_ctrl,&g_uart2_cfg);
	
	assert(FSP_SUCCESS==err);

}
volatile bool uart2_send_complete_flag = false;

void uart2_callback(uart_callback_args_t *p_args){
	
	switch(p_args -> event){
		case UART_EVENT_RX_CHAR:{
		
			break;
		}
		case UART_EVENT_TX_COMPLETE:{
			uart2_send_complete_flag = true;
			break;
		}
		default:
			break;
	}

	
	
}

//////////雷达串口
void UART3_Init(void){
	
	err=R_SCI_UART_Open(&g_uart3_ctrl,&g_uart3_cfg);
	
	assert(FSP_SUCCESS==err);

}
volatile bool uart3_send_complete_flag = false;

void uart3_callback(uart_callback_args_t *p_args){
	
	switch(p_args -> event){
		case UART_EVENT_RX_CHAR:{
		
			break;
		}
		case UART_EVENT_TX_COMPLETE:{
			uart3_send_complete_flag = true;
			break;
		}
		default:
			break;
	}

	
	
}
 
/////////////////4g雷达
void UART8_Init(void){
	err=R_SCI_UART_Open(&g_uart8_ctrl,&g_uart8_cfg);
	
	assert(FSP_SUCCESS==err);

}

volatile bool uart8_send_complete_flag = false;

void uart8_callback(uart_callback_args_t *p_args){
	
	switch(p_args -> event){
		case UART_EVENT_RX_CHAR:{
        ceshi = 1;
			break;
		}
		case UART_EVENT_TX_COMPLETE:{
			uart8_send_complete_flag = true;
			break;
		}
		default:
			break;
	}

	
	
}
////////////////////4GGPS
void UART9_Init(void){
	err=R_SCI_UART_Open(&g_uart9_ctrl,&g_uart9_cfg);
	
	assert(FSP_SUCCESS==err);

}

volatile bool uart9_send_complete_flag = false;

void uart9_callback(uart_callback_args_t *p_args){
	
	switch(p_args -> event){
		case UART_EVENT_RX_CHAR:{

			break;
		}
		case UART_EVENT_TX_COMPLETE:{
			uart9_send_complete_flag = true;
			break;
		}
		default:
			break;
	}

	
	
}