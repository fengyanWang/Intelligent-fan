#include "uart.h"
#include "STC12C5A60S2.h"
#include "TC_Read.h"
#include "motor.h"
#include "data_parse.h"
#include "key.h"
#include "global.h"

#define T2	0	//�����ʼ�¶�

u16 Kp1 = 8;		//�����²����ϵ��
u8 CurrentSpeed = 0; //���嵱ǰ�ٶ�
u8 SpeedInc = 25; //�ٶ�����
BOOL gDir = 1;	//����1����0����
BOOL gStopFlag = 1; //ֹͣ��־λ0ֹͣ1����

BOOL AutoMode = 1; //�Զ�ģʽ
BOOL KeyCtlMode = 0;//��������ģʽ
BOOL BtCtlMode	= 0 ;//��������ģʽ

u32 time = 0;

void main()
{
	float t1=0;
	float tmpDiff=0;
	
	u8 speed=0;
	/* ȫ������ΪIOģʽ */
	P0M0 = 0x00;
	P0M1 = 0x00;
	P1M0 = 0x00;
	P1M1 = 0x00;
	P2M0 = 0x00;
	P2M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x00;
	P4M0 = 0x00;
	P4M1 = 0x00;
	P12 = 1; //�رշ�����
	uartInit(); //9600 bade ��ʼ������
	TC_Init(); //��ʼ���¶ȼ�
	motorInit();//��ʼ�����
	//SendString("Init Ok\r\n");
	motorSetDir(gDir);
	
	while(1)
	{	
		
		TC_Read(&t1); //��ȡ��ǰ�¶�
//		printf("T1:%f\r\n",t1);
//		DelayMs(200);

	if(AutoMode)
	{
		gStopFlag = 1;
		tmpDiff = t1-T2;
		if(tmpDiff<0)//�¶Ȳ�С��0����ת
		{
			gDir = 0; //��ת
			tmpDiff = -tmpDiff;
		}
		else//�²����0����ת
		{
			gDir = 1;
		}
		CurrentSpeed = (u8)Kp1*tmpDiff;
	}
	//printf("gFrameCount:%d\n",(int)gFrameCount);
	if(gCmdFlag==1)
	{
		//printf("Recieved cmd\n");
		CmdParse(); //�������ݽ��� �ŵ������жϺ�����ִ��
		gCmdFlag = 0;
	}
//	if(BtCtlMode)
//	{
//		printf("BTCtlMode\r\n");
//	}
		if(!BtCtlMode) //��������밴������ģʽ���˳����˳�ģʽ
		{
			//printf("Key Mode\r\n");
			KeyScan(0); //��ⰴ���Ƿ񱻰���
		}
		
		motorCtl(); //���õ�ǰ�ٶ�
		/* ����λ�������¶ȣ��ٶ����� */
		if(time++ == 200)
		{
			printf("T:%f\n",t1);
			printf("speed:%d\n",(int)CurrentSpeed);
			time = 0;
		}			
	}
		
	
}
