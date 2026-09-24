#include "hal_adc.h"

void ADC_Init(void){
	fsp_err_t err;
	err = R_ADC_Open(&g_adc0_ctrl,&g_adc0_cfg);
	err = R_ADC_ScanCfg(&g_adc0_ctrl,&g_adc0_channel_cfg);
	assert(FSP_SUCCESS == err);
}
volatile bool scan_complete_flag = false;
void ADC0_callback(adc_callback_args_t * p_args){
	 scan_complete_flag = true;
}
Adc_Result Read_adc_value(void){
	uint16_t adc_tds_data;
	uint16_t adc_ph_data;
	uint16_t adc_ts300b_data; 
	uint16_t adc_yang_data;
	Adc_Result result;
	R_ADC_ScanStart(&g_adc0_ctrl);
	while(!scan_complete_flag){
	}
	scan_complete_flag = false;
	R_ADC_Read(&g_adc0_ctrl,ADC_CHANNEL_2,&adc_tds_data);//002    
	R_ADC_Read(&g_adc0_ctrl,ADC_CHANNEL_4,&adc_ph_data);//004 
	R_ADC_Read(&g_adc0_ctrl,ADC_CHANNEL_5,&adc_ts300b_data);//005
	R_ADC_Read(&g_adc0_ctrl,ADC_CHANNEL_10,&adc_yang_data);//010
	result.TDS_value = 66.71*(pow( 21*adc_tds_data * (5.0f / 4096.0f),3))-127.93*(pow( 21*adc_tds_data * (5.0f / 4096.0f),2))+428.7* 21*adc_tds_data * (5.0f / 4096.0f);
	result.PH_value = -5.6342*adc_ph_data * (5.0f /4096.0f)+16.413;
	result.TS300B_value = -865.68*adc_ts300b_data * (5.0f /4095.0f)+2047.19;
	result.YANG_value = 0.004884f *adc_yang_data;
	return result;
}
