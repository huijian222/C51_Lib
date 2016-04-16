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
	ET0=1; //������ʱ��0�ж�
	TR0=1; //������ʱ��
	IT0=1;	   
	EX0=1;	   //�ⲿ�ж�0����
	EA=1;//���ж�
 	SCON=0x50;
 	EA=1;
 	ES=1;
 	TR1=1;
 	TH1=0xfd;
 	TL1=0xfd;
}



 void inter0() interrupt 0	//�ⲿ�ж�0����	�ж�100�β鿴�ж��˶��ٸ�0.5msȻ��  ��N=�жϴ���
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
	SBUF=(dat/100)+ 48;			// ���� �� λ 
	while(!TI);
	TI=0;
	SBUF=(dat%100/10)+48;		// ���� ʮ λ 
	while(!TI);
	TI=0;
	SBUF=(dat%10)+48;			// ���� �� λ 
	while(!TI);
	TI=0;
}

void timer0() interrupt 1	 //��ʱ��1ÿ0.5MS�ж�һ��  ����ֱ�����������ֵ �Լ�����PWM����
{
	t=t+0.0011625;  //ʹ��Ƶ�ʼ� ��������ж�����ʱ��
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