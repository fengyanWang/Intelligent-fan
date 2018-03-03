#include "uart.h"
#include "STC12C5A60S2.h"
#include "TC_Read.h"
#include "motor.h"
#include "data_parse.h"
#include "key.h"
#include "global.h"

#define T2	0	//定义初始温度

u16 Kp1 = 8;		//定义温差比例系数
u8 CurrentSpeed = 0; //定义当前速度
u8 SpeedInc = 25; //速度增量
BOOL gDir = 1;	//方向1正向0反向
BOOL gStopFlag = 1; //停止标志位0停止1运行

BOOL AutoMode = 1; //自动模式
BOOL KeyCtlMode = 0;//按键控制模式
BOOL BtCtlMode	= 0 ;//蓝牙控制模式

u32 time = 0;

void main()
{
	float t1=0;
	float tmpDiff=0;
	
	u8 speed=0;
	/* 全部设置为IO模式 */
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
	P12 = 1; //关闭蜂鸣器
	uartInit(); //9600 bade 初始化蓝牙
	TC_Init(); //初始化温度计
	motorInit();//初始化电机
	//SendString("Init Ok\r\n");
	motorSetDir(gDir);
	
	while(1)
	{	
		
		TC_Read(&t1); //读取当前温度
//		printf("T1:%f\r\n",t1);
//		DelayMs(200);

	if(AutoMode)
	{
		gStopFlag = 1;
		tmpDiff = t1-T2;
		if(tmpDiff<0)//温度差小于0，反转
		{
			gDir = 0; //反转
			tmpDiff = -tmpDiff;
		}
		else//温差大于0，正转
		{
			gDir = 1;
		}
		CurrentSpeed = (u8)Kp1*tmpDiff;
	}
	//printf("gFrameCount:%d\n",(int)gFrameCount);
	if(gCmdFlag==1)
	{
		//printf("Recieved cmd\n");
		CmdParse(); //蓝牙数据解析 放到串口中断函数中执行
		gCmdFlag = 0;
	}
//	if(BtCtlMode)
//	{
//		printf("BTCtlMode\r\n");
//	}
		if(!BtCtlMode) //任意键进入按键控制模式，退出键退出模式
		{
			//printf("Key Mode\r\n");
			KeyScan(0); //监测按键是否被按下
		}
		
		motorCtl(); //设置当前速度
		/* 向上位机发回温度，速度数据 */
		if(time++ == 200)
		{
			printf("T:%f\n",t1);
			printf("speed:%d\n",(int)CurrentSpeed);
			time = 0;
		}			
	}
		
	
}
