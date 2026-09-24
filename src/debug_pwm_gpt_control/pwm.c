#include "headfile.h"
void pwm_setduty(int32_t us_A, int32_t us_B)
{
    timer_info_t info;
    int32_t duty_count_A, duty_count_B;
    const int32_t MIN_US = 500;  // 电调最小值
    const int32_t MAX_US = 2500;  // 电调最大值

    // 限幅（保护电调，PID不会超范围）
    if(us_A < MIN_US) us_A = MIN_US;
    if(us_A > MAX_US) us_A = MAX_US;
    if(us_B < MIN_US) us_B = MIN_US;
    if(us_B > MAX_US) us_B = MAX_US;

    // 获取定时器总周期（官方标准用法）
    R_GPT_InfoGet(&g_timer7_ctrl, &info);

    // 公式：计数值 = 总周期 * 脉宽(us) / 20000us
    duty_count_A = (info.period_counts * us_A) / 20000;
    duty_count_B = (info.period_counts * us_B) / 20000;

    // 双路PWM输出
    R_GPT_DutyCycleSet(&g_timer7_ctrl, duty_count_A, GPT_IO_PIN_GTIOCA);
    R_GPT_DutyCycleSet(&g_timer7_ctrl, duty_count_B, GPT_IO_PIN_GTIOCB);
}

void pwm_init(void){

	R_GPT_Open(&g_timer7_ctrl,&g_timer7_cfg);
	
	R_GPT_Start(&g_timer7_ctrl);
	
	pwm_setduty(1500, 1500);  // 1500=停止（中位）
	R_BSP_SoftwareDelay(2, BSP_DELAY_UNITS_SECONDS);
	
}
