#include "bsp_dmac.h"
//extern volatile int  N10_data[18];
//extern char str_n10_data[110];
extern volatile int MOVE_Lock;
extern volatile int move;
extern volatile int v;
extern volatile int jixiebi;//机械臂编号
extern volatile int jixiebi_value;//机械臂占空比
extern volatile uint8_t sci9_rx_data[size9];
extern volatile double GPS_LNG_USE ;
extern volatile double GPS_LAT_USE ;
extern  char light[6];
extern int arrive_flag;
extern char analyze[90];
char GPS_LNG[16];
char GPS_LAT[16];
int buff_len = 0;
char tx_buffer[20]; 
extern volatile int ceshi;
////////////
void analyze_chuli(void){////分析接收数据
	
	if(strstr(sci8_rx_data, "light_on")){
	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_08_PIN_04   , 1);
		snprintf(light, sizeof(light), "true");}
	if(strstr(sci8_rx_data, "light_off")){
	R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_08_PIN_04   , 0);
		snprintf(light, sizeof(light), "false");
	}
	printf("{\"id\":\"123\",\"version\":\"1.0\",\"params\":{\"light\":{\"value\":%s}}}",light);
	if(strstr(analyze, "up")){//前
	move = 1;
	}
	if(strstr(analyze, "down")){//下
	move = 3;
	}
	if(strstr(analyze, "left")){//左
	move = 2;
	}
	if(strstr(analyze, "right")){//右
	move = 4;
	}
	if(strstr(analyze, "stop")){//右
	move = 0;
	}
	if(strstr(analyze, "arrive")){//右
	arrive_flag = 1;
	}
}
int fputc(int ch, FILE *f)
{   
		fsp_err_t err=FSP_SUCCESS;
	//  (void)f;
		err = R_SCI_UART_Write(&g_uart8_ctrl, (uint8_t *)&ch, 1);
		if(FSP_SUCCESS != err) __BKPT();
		while(uart8_send_complete_flag == false){}
		uart8_send_complete_flag = false; 
		return ch;
	}
//////////imudma uart5 rx502 tx501
void DMAC_Init(void)
{
	fsp_err_t err;    

	err =g_transfer_on_dmac.open(g_transfer_dmac_rx.p_ctrl,g_transfer_dmac_rx.p_cfg);
	assert(FSP_SUCCESS == err);
	err =g_transfer_on_dmac.enable(g_transfer_dmac_rx.p_ctrl);
	assert(FSP_SUCCESS == err);
}
void set_transfer_length(transfer_cfg_t const * const p_config, volatile uint16_t _length)
{
	p_config->p_info->length = _length;
}
void set_transfer_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest)
{
	p_config->p_info->p_src = (void const * volatile) _p_src;
	p_config->p_info->p_dest = (void * volatile) _p_dest;
}	
volatile uint8_t dmac_sci_tx_flag =0;
volatile uint8_t dmac_sci_rx_flag =0;

void transfer_dmac_tx_callback(dmac_callback_args_t *p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
	dmac_sci_tx_flag =1;
}
void transfer_dmac_rx_callback(dmac_callback_args_t *p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
		gyro.WzL=sci_rx_data[6];
		gyro.WzH=sci_rx_data[7];
		gyro.gyroZ=(float)((gyro.WzH<<8)|gyro.WzL)/32768*2000;
		angle.YawL=sci_rx_data[17];
		angle.YawH=sci_rx_data[18];
		angle.angleZ=(float)((angle.YawH<<8)|angle.YawL)/32768*180;
	dmac_sci_rx_flag =1;
	g_transfer_on_dmac.open(g_transfer_dmac_rx.p_ctrl,g_transfer_dmac_rx.p_cfg);
	g_transfer_on_dmac.enable(g_transfer_dmac_rx.p_ctrl);
}
////////////loradma uart2 tx302 rx301
void DMAC2_Init(void)
{
	fsp_err_t err;    

	err =g_transfer_on_dmac.open(g2_transfer_dmac_rx.p_ctrl,g2_transfer_dmac_rx.p_cfg);
	assert(FSP_SUCCESS == err);
	err =g_transfer_on_dmac.enable(g2_transfer_dmac_rx.p_ctrl);
	assert(FSP_SUCCESS == err);
}
volatile uint8_t dmac2_sci_tx_flag =0;
volatile uint8_t dmac2_sci_rx_flag =0;

void transfer2_dmac_rx_callback(dmac_callback_args_t *p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
	switch(sci2_rx_data[0])
    {
        case 0xEE:
            // 屏幕
				switch(sci2_rx_data[1])
				{
						case 0x01:
            // 白	
										switch(sci2_rx_data[2])
								{
										case 0x01:
										// 灯
												switch(sci2_rx_data[3])
												{
													case 0x00:
													// 关闭
													WS2812_AllOff();
														break;
													case 0x01:
													// 红
													WS2812_AllRed();
														break;
													case 0x02:
													// 白
													WS2812_AllWhite();
														break;
													case 0x03:
													// 绿
													WS2812_AllGreen();
														break;
													case 0x04:
													// 紫
													WS2812_AllPurple();
														break;
													case 0x05:
													// 青
													WS2812_AllCyan();
														break;
													case 0x06:
													// 彩色
													WS2812_StaticMultiColor();
														break;
												}
												break;
										case 0x02:
										// 泵
											R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_04_PIN_06,sci2_rx_data[3]);
												break;
										case 0x03:
										// 云台上
												pwm_setdutyshang(sci2_rx_data[3]);
												break;
										case 0x04:
										// 云台左右
												pwm_setdutyzuo(sci2_rx_data[3]);
												break;
										case 0x05:
										// 机械臂编号
												jixiebi = sci2_rx_data[3];
												break;
										case 0x06:
										// 占空比
												jixiebi_value = 600+sci2_rx_data[3]*18;
													buff_len = sprintf(tx_buffer, "#00%dP%dT0400!/r/n", jixiebi,jixiebi_value);
														R_SCI_UART_Write(&g_uart3_ctrl,(uint8_t *)tx_buffer,buff_len);
												break;
										case 0x07:
										// 速度
												v = sci2_rx_data[3];
												break;
										case 0x08:
										// 速度
												MOVE_Lock = sci2_rx_data[3];
												break;
								}
						break;
						case 0x02:
            // 黑
								break;  
				}
				
            break;
        case 0xCC:
            // 摇杆
						move = sci2_rx_data[2];
            break;
    }
	dmac2_sci_rx_flag =1;
	g_transfer_on_dmac.open(g2_transfer_dmac_rx.p_ctrl,g2_transfer_dmac_rx.p_cfg);
	g_transfer_on_dmac.enable(g2_transfer_dmac_rx.p_ctrl);
	
}
void set_transfer2_length(transfer_cfg_t const * const p_config, volatile uint16_t _length)
{
	p_config->p_info->length = _length;
}
void set_transfer2_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest)
{
	p_config->p_info->p_src = (void const * volatile) _p_src;
	p_config->p_info->p_dest = (void * volatile) _p_dest;
}	
//////////机械臂串口 uart3 tx707 rx706 
void DMAC3_Init(void) 
{
	fsp_err_t err;    
	err =g_transfer_on_dmac.open(g3_transfer_dmac_rx.p_ctrl,g3_transfer_dmac_rx.p_cfg);
	assert(FSP_SUCCESS == err);
	err =g_transfer_on_dmac.enable(g3_transfer_dmac_rx.p_ctrl);
	assert(FSP_SUCCESS == err);
}
volatile uint8_t dmac3_sci_tx_flag =0;
volatile uint8_t dmac3_sci_rx_flag =0;
void transfer3_dmac_rx_callback(dmac_callback_args_t *p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
//		N10_data[0] = (((uint16_t)sci3_rx_data[5] << 8) + sci3_rx_data[6]) / 100.0f;
////		N10_data[0]=(int)
//    N10_data[17] =(((uint16_t)sci3_rx_data[55] << 8) + sci3_rx_data[56]) / 100.0f;
//		for(int i = 0;i<=15;i=i+1){
//		N10_data[i+1] = (((uint16_t)sci3_rx_data[3*i+7] << 8) + sci3_rx_data[3*i+8]);
//		}
//		str_n10_data[0] = '\0';
//		memset(str_n10_data, 0, sizeof(str_n10_data)); 
//		for (int i = 0; i < 18; i++) {
//    char temp[20];
//    sprintf(temp, "%d", (int)(N10_data[i]+0.5f)); // 数字转字符串
//    
//    strcat(str_n10_data, temp);             // 拼接数字
//    
//    if (i < 17) strcat(str_n10_data, ",");  // 如果不是最后一个，拼接逗号
//	}
//		
  	dmac3_sci_rx_flag =1;
	g_transfer_on_dmac.open(g3_transfer_dmac_rx.p_ctrl,g3_transfer_dmac_rx.p_cfg);
	g_transfer_on_dmac.enable(g3_transfer_dmac_rx.p_ctrl);
	
}
void set_transfer3_length(transfer_cfg_t const * const p_config, volatile uint16_t _length)
{
	p_config->p_info->length = _length;
}
void set_transfer3_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest)
{
	p_config->p_info->p_src = (void const * volatile) _p_src;
	p_config->p_info->p_dest = (void * volatile) _p_dest;
}	
////////////4g串口 uart8 txA00 rx607
void DMAC8_Init(void)
{
	fsp_err_t err;    
	err =g_transfer_on_dmac.open(g8_transfer_dmac_rx.p_ctrl,g8_transfer_dmac_rx.p_cfg);
	assert(FSP_SUCCESS == err);
	err =g_transfer_on_dmac.enable(g8_transfer_dmac_rx.p_ctrl);
	assert(FSP_SUCCESS == err);
}
volatile uint8_t dmac8_sci_tx_flag =0;
volatile uint8_t dmac8_sci_rx_flag =0;
void transfer8_dmac_rx_callback(dmac_callback_args_t *p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
	ceshi++;
	analyze_chuli();
	for(int j=0;j<=59;j++){
		sci8_rx_data[j] = 0;
	}
  dmac8_sci_rx_flag =1;
	g_transfer_on_dmac.open(g8_transfer_dmac_rx.p_ctrl,g8_transfer_dmac_rx.p_cfg);
	g_transfer_on_dmac.enable(g8_transfer_dmac_rx.p_ctrl);
	
}
void set_transfer8_length(transfer_cfg_t const * const p_config, volatile uint16_t _length)
{
	p_config->p_info->length = _length;
}
void set_transfer8_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest)
{
	p_config->p_info->p_src = (void const * volatile) _p_src;
	p_config->p_info->p_dest = (void * volatile) _p_dest;
}	
///////////////////////gps-4g tx203 rx202
void DMAC9_Init(void)
{
	fsp_err_t err;    
	err =g_transfer_on_dmac.open(g9_transfer_dmac_rx.p_ctrl,g9_transfer_dmac_rx.p_cfg);
	assert(FSP_SUCCESS == err);
	err =g_transfer_on_dmac.enable(g9_transfer_dmac_rx.p_ctrl);
	assert(FSP_SUCCESS == err);
}
volatile uint8_t dmac9_sci_tx_flag =0;
volatile uint8_t dmac9_sci_rx_flag =0;
void transfer9_dmac_rx_callback(dmac_callback_args_t *p_args)
{
	FSP_PARAMETER_NOT_USED(p_args);
////
	for(int i = 4;i<19;i++){
		GPS_LNG[i-4]=sci9_rx_data[i];
	}
	for(int i = 24;i<39;i++){
		GPS_LAT[i-24]=sci9_rx_data[i];
	}
	GPS_LNG[15] = '\0';
	GPS_LAT[15] = '\0';
	GPS_LNG_USE = atof(GPS_LNG);
	GPS_LAT_USE = atof(GPS_LAT);
  	dmac9_sci_rx_flag =1;
	g_transfer_on_dmac.open(g9_transfer_dmac_rx.p_ctrl,g9_transfer_dmac_rx.p_cfg);
	g_transfer_on_dmac.enable(g9_transfer_dmac_rx.p_ctrl);
	
}
void set_transfer9_length(transfer_cfg_t const * const p_config, volatile uint16_t _length)
{
	p_config->p_info->length = _length;
}
void set_transfer9_dst_src_address(transfer_cfg_t const * const p_config,const volatile uint8_t * _p_src,const volatile uint8_t * _p_dest)
{
	p_config->p_info->p_src = (void const * volatile) _p_src;
	p_config->p_info->p_dest = (void * volatile) _p_dest;
}	
