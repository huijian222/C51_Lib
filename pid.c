#include "pid.h"
extern float f;
	_pid pid;
void PID_init(){
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;		//
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=4.0;   //200 p:0.07jike 
    pid.Ki=0.0;
    pid.Kd=0.0;
}

float PID_realize(float speed ,float actual){
	pid.ActualSpeed=actual/MaxActual;	   //MaxActual 在pid.h中定义
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    pid.integral+=pid.err;
    pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    return pid.ActualSpeed;
}

float PID_application(float target){
	float PID_num;
	PID_num=PID_realize(target,f);
	if(PID_num > 1){
		PID_num = 1.0;
	}
	if(PID_num < -1){
		PID_num = -1.0;
	}
	PID_num=(PID_num+1.0)/2.0;
	return PID_num;
}