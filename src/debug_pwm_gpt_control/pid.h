#ifndef PID_H_
#define PID_H_

#include "headfile.h"

typedef struct {
    float kp,ki,kd;                 			//P,I,D参数
    float error,error_last,error_last2;   //误差
    float integral,maxintegral;     			//积分器
    float output,output_1,maxOutput;			//输出限制
    float target;                   			//目标期望
		float dead;														//死区
}pid;

void pid_init(pid* pid_struct,
              float kp,
              float ki,
              float kd,
              float maxIntegral,
              float maxOutput,
              float target,
							float dead);

float pid_increm(pid* pid_struct,float now_value);    				//增量式pid
							
float pid_location(pid* pid_struct,float now_value);  				//位置式pid
							
void pid_target(pid* pid_struct,float target);    						//改变期望值
							
void pid_change(pid* pid_struct,float kp,float ki,float kd);	//改变参数
			
#endif							