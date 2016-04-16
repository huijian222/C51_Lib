#include "STC5A60S2.h"
#include "xiaweiji.h"
#include "main.h"
#include "pid.h"
u8 numx[16];	
float t=0,n=0,f=0 ,target_speed = 0;
u16 flag, nn, k ;
void init_com(){
	TMOD=0x21;//
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
	ET0=1; //开启定时器0中断
	TR0=1; //启动定时器
	IT0=1;	   
	EX0=1;	   //外部中断0计数
	EA=1;//总中断
 	SCON=0x50;
 	EA=1;
 	ES=1;
 	TR1=1;
 	TH1=0xfd;
 	TL1=0xfd;
}



 void inter0() interrupt 0	//外部中断0计数	中断100次查看中断了多少个0.5ms然后  让N=中断次数
{

		nn=nn+1;
		if(nn>=100){
		nn=0;  
		n=t;  
		t=0;
		}
		if(nn<0){
			nn=0;
		}
																										  
}
void Send(u16 dat){
	SBUF=(dat/100)+ 48;			// 发送 百 位 
	while(!TI);
	TI=0;
	SBUF=(dat%100/10)+48;		// 发送 十 位 
	while(!TI);
	TI=0;
	SBUF=(dat%10)+48;			// 发送 个 位 
	while(!TI);
	TI=0;
}

void timer0() interrupt 1	 //定时器1每0.5MS中断一次  测量直流电机的脉冲值 以及进行PWM调速
{
	t=t+0.0011625;  //使用频率计 测出具体中断所需时间
	TH0=(65536-500)/256;
	TL0=(65536-500)%256;
	if(t >= 1){
		n=0.00000;
	}
	flag++;
}
void Inter() interrupt 4
{
	_pid pid;
	if(RI==1){
		RI=0;
		   numx[k]=SBUF;	
		   k++;
		   if(k==16){
		    k=0;
			pid.Kp=numx[0]+numx[1]*10+ numx[2]*100+numx[3]*1000;
			pid.Ki=numx[4]+numx[5]*10+ numx[6]*100+numx[7]*1000;
			pid.Kd=numx[8]+numx[9]*10+ numx[10]*100+numx[11]*1000;
			target_speed=numx[12]+numx[13]*10+ numx[14]*100+numx[15]*1000;
		   }	   		  	   
	}
}