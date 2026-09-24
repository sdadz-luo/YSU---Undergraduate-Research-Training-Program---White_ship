#ifndef PWM_H_
#define PWM_H_

#include "headfile.h"

void pwm_init(void);
void pwm_setduty(int32_t us_A, int32_t us_B);

#endif