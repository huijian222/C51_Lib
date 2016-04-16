#include "STC5A60S2.h"
#include "main.h"
#include "xiaweiji.h"
#include "pid.h"
#include "pwm.h"

u16 pwm = 9999;
extern float target_speed;
extern u16 flag;
extern float f;
extern void PWMn_init(unsigned int high);
extern void PWMn_SetHighReg(unsigned int high);
extern float PID_application(float target);
extern void Send(u16 dat);

u8 usb[40]="ssss";

void init_all(void){

	init_com();	   //串口初始化
	PID_init();	
}
void main(void){
	init_all();
	PWMn_init(pwm);
	PWMn_SetHighReg(pwm);
	//sendAll(usb);
	while(1){
		//Send(f);
		if(flag >= 200){
		//	pwm = PID_application(target_speed) * PWM_DUTY;  //在pwm.h中可以修改 PWM_DUTY 	
			flag = 0;
		}
	}	
}