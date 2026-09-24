#ifndef BSP_DMAC_H_
#define BSP_DMAC_H_
#include "hal_data.h"
#include "stdio.h"
#define size 22
#define size2 6
#define size3 58
#define size8 60
#define size9 39
extern volatile bool uart_send_complete_flag;
extern volatile bool uart2_send_complete_flag;
extern volatile bool uart3_send_complete_flag;
extern volatile bool uart8_send_complete_flag;
extern volatile bool uart9_send_complete_flag;
extern uint8_t sci_rx_data[size];
extern uint8_t sci2_rx_data[size2];
extern uint8_t sci3_rx_data[size3];
extern uint8_t sci8_rx_data[size8];
extern volatile uint8_t sci9_rx_data[size9];
void DMAC_Init(void);
void DMAC2_Init(void);
void DMAC3_Init(void);
void DMAC8_Init(void);
void DMAC9_Init(void);
void transfer_dmac_rx_callback(dmac_callback_args_t *p_args);
void transfer2_dmac_rx_callback(dmac_callback_args_t *p_args);
void transfer3_dmac_rx_callback(dmac_callback_args_t *p_args);
void transfer8_dmac_rx_callback(dmac_callback_args_t *p_args);
void transfer9_dmac_rx_callback(dmac_callback_args_t *p_args);
void set_transfer_length(transfer_cfg_t const * const p_config, volatile uint16_t _length);
void set_transfer_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest);
void set_transfer2_length(transfer_cfg_t const * const p_config, volatile uint16_t _length);
void set_transfer2_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest);
void set_transfer3_length(transfer_cfg_t const * const p_config, volatile uint16_t _length);
void set_transfer3_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest);
void set_transfer8_length(transfer_cfg_t const * const p_config, volatile uint16_t _length);
void set_transfer8_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest);
void set_transfer9_length(transfer_cfg_t const * const p_config, volatile uint16_t _length);
void set_transfer9_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest);
//////imu½á¹¹Ìå
typedef struct
{  uint8_t WxL;
   uint8_t WxH;
   uint8_t WyL;
   uint8_t WyH;
   uint8_t WzL;
   uint8_t WzH;
	 int gyroX;
	 int gyroY;
	 float gyroZ;
}gyroTypeDef;
typedef struct
{  uint8_t RollL;
	 uint8_t RollH;
	 uint8_t PitchL;
	 uint8_t PitchH;
	 uint8_t YawL;
	 uint8_t YawH;
	 double angleX;
	 double angleY;
	 double angleZ;
}angleTypeDef;
extern gyroTypeDef gyro;
extern angleTypeDef angle;
#endif 
