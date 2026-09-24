#include "headfile.h"
#include "../debug_uart/bsp_dmac.h"
extern volatile int jixiebi;//��е�۱��
extern volatile int jixiebi_value;//��е��ռ�ձ�
extern char analyze[90];
pid pid_gyro;
extern volatile int MOVE_Lock;
extern volatile int move;
extern volatile int v;
float pwm_turn = 0,pwm_l = 0,pwm_r = 0;

void gpt0_init(void){

	R_GPT_Open(&time0_ctrl,&time0_cfg);
	
	R_GPT_Start(&time0_ctrl);
	
	pid_init(&pid_gyro,5,0,0,1000,500,0,0);
	
}

void time0_callback(timer_callback_args_t *p_args){

    /* ---- PID ���� ---- */

	if(gyro.gyroZ > 2000) gyro.gyroZ -= 4000;
	
    pwm_turn = pid_location(&pid_gyro, gyro.gyroZ);

    if (MOVE_Lock)
    {
			pwm_l = 1500 + 100* v;
			pwm_r = 1500 + 100* v;
			
        switch (move)
        {
            case MOVE_STOP: pwm_l = 0; pwm_r = 0; break;
            case MOVE_LEFT: pwm_l = 1500 - 100 * v; pwm_turn = 0; break;
            case MOVE_RIGHT: pwm_r = 1500 - 100 * v; pwm_turn = 0; break;
            case MOVE_BACKWARD: pwm_l = 1500 - 100 * v; pwm_r = 1500 - 100 * v; break;
            default: break;
        }
        pwm_setduty(pwm_l - pwm_turn, pwm_r + pwm_turn);
    }
    else
    {
        /* ������ģʽ���� PID ��������ǰ���ٶ� */
        pwm_setduty(1500-pwm_turn,1500 + pwm_turn);
    }
	
}