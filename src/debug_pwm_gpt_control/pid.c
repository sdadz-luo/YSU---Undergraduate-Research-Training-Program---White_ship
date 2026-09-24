#include "headfile.h"

void pid_init(pid* pid_struct,
              float kp,
              float ki,
              float kd,
              float maxIntegral,
              float maxOutput,
              float target,
							float dead){
    pid_struct ->  kp           =kp;
    pid_struct ->  ki           =ki;
    pid_struct ->  kd           =kd;
    pid_struct ->  error        =0;
    pid_struct ->  error_last   =0;
    pid_struct ->  error_last2  =0;
    pid_struct ->  integral     =0;
    pid_struct ->  maxintegral  =maxIntegral;
    pid_struct ->  output       =0;
    pid_struct ->  output_1     =0;
    pid_struct ->  maxOutput    =maxOutput;
    pid_struct ->  target       =target;
		pid_struct ->  dead       	=dead;			
}

float pid_increm(pid* pid_struct,float now_value){
    //误差处理
    pid_struct->error_last2  =   pid_struct->error_last;              //保存上上次误差
    pid_struct->error_last   =   pid_struct->error;                   //保存上一次误差
    pid_struct->error 		   =   pid_struct->target - now_value;      //接受本次误差
	
		//输出计算
    pid_struct->output_1 = pid_struct->kp  *  (pid_struct->error - pid_struct->error_last)                   							//比例
                         +  pid_struct->ki *   pid_struct->error                                 													//积分
                         +  pid_struct->kd *  (pid_struct->error - 2*(pid_struct->error_last) + pid_struct->error_last2); //微分
	
    pid_struct->output   += pid_struct->output_1;
	
	//死区处理
	if (fabs(pid_struct->error) > pid_struct->dead){
		pid_struct->output_1 *= 1;
	}else{
		pid_struct->output_1 *= 0.95;
	}
	
	 //输出限幅
   if(pid_struct->output  >     pid_struct->maxOutput )      pid_struct->output = pid_struct->maxOutput;
   if(pid_struct->output  <   -(pid_struct->maxOutput))      pid_struct->output = -(pid_struct->maxOutput);

	return pid_struct->output;
}

float pid_location(pid* pid_struct,float now_value){
    //误差处理
	pid_struct->error_last2  =   pid_struct->error_last;              //保存上上次误差
  pid_struct->error_last   =   pid_struct->error;                   //保存上一次误差
  pid_struct->error 		   =   pid_struct->target - now_value;      //接受本次误差
	
	//死区处理
	if (fabs(pid_struct->error) >= pid_struct->dead){
		
    //积分处理
    pid_struct->integral   +=  pid_struct->error;
    if(pid_struct->integral >   pid_struct->maxintegral )    pid_struct->integral= pid_struct->maxintegral;
    if(pid_struct->integral < -(pid_struct->maxintegral))    pid_struct->integral=-pid_struct->maxintegral;
		
    //输出计算
    pid_struct->output = pid_struct->kp *   pid_struct->error                                    //比例
                       + pid_struct->ki *   pid_struct->integral                                 //积分
                       + pid_struct->kd *  (pid_struct->error-pid_struct->error_last);           //微分
	}else{
		pid_struct->output = 0;
	}

    //输出限幅
    if(pid_struct->output  >     pid_struct->maxOutput )      pid_struct->output=pid_struct->maxOutput;
    if(pid_struct->output  <   -(pid_struct->maxOutput))      pid_struct->output=-(pid_struct->maxOutput);

    return pid_struct->output;
}

void pid_target(pid* pid_struct,float target){
    pid_struct -> target = target;
}

void pid_change(pid* pid_struct,float kp,float ki,float kd){
    pid_struct ->  kp  =kp;
    pid_struct ->  ki  =ki;
    pid_struct ->  kd  =kd;
}
