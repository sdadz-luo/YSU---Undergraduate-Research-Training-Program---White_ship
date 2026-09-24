#ifndef HAL_ADC_H_
#define HAL_ADC_H_
#include "hal_data.h"
void ADC_Init(void);

typedef struct {
    float PH_value; 
    float TDS_value;  
		float TS300B_value;
		float YANG_value;
}Adc_Result;
Adc_Result Read_adc_value(void);
#endif