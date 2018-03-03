#include "data_parse.h"
#include "global.h"
#include "delay.h"
#include "STC12C5A60S2.h"
#include "uart.h"

u8 CmdArr[8]={0};//接收到的蓝牙命令存放数组
//u8 SpeedRatio=0;//转速比
//u8 TemperatureRatio=0;//温差比

/******************************************
* Function Name  : CmdParse
* Description    : Bluetooth command resolution
* Input          : None
* Output         : None
* Return         : 解析出来的命令
*******************************************/
void CmdParse(void)
{
	static u16 Count1=0;
	static u16 Count2=0;
//	int i;
//	for(i=0;i<6;i++)
//	{
//		SendData(CmdArr[i]);
////		printf("%d",(u8)CmdArr[i]);
//	}
	if((CmdArr[0]==0XA5)&&(CmdArr[1]==0X5A)&&(CmdArr[2]==0X04)&&(CmdArr[5]==0XAA))
	{
		BtCtlMode = 1;//进入蓝牙控制模式
		//KeyCtlMode = 0;
		AutoMode = 0;
		if((CmdArr[3]==0XB1)&&(CmdArr[4]==0XB5))
		{
			Count1++;
			if(Count1%2==1)
			{
				
				gStopFlag = 0;//stop
				printf("run\r\n");
			}
			else
			{
				gStopFlag=1;//run
				printf("stop\r\n");
			} 
		}
		else if((CmdArr[3]==0XB2)&&(CmdArr[4]==0XB6))
		{
			Count2++;
			if(Count2%2==1)
			{
				//return PositiveDir_Flag;
				gDir = 1;
				printf("Positive\r\n");
			}
			else
			{
				//return NegativeDir_Flag;
				gDir = 0;
				printf("Negative\r\n");
			}
		}
		else if((CmdArr[3]==0XB3)&&(CmdArr[4]==0XB7))
		{
			//return SpeedInc_Flag;
			printf("speed up\r\n");
			if(255-CurrentSpeed<25)
			{
				CurrentSpeed=255;
				
			}else
			{
				CurrentSpeed += SpeedInc;
			}
			
		}
		else if((CmdArr[3]==0XB4)&&(CmdArr[4]==0XB8))
		{
			//return SpeedDec_Flag;
			if(CurrentSpeed<25)
			{
				CurrentSpeed=0;
			}else
			{
				CurrentSpeed -= SpeedInc;
			}
			
			printf("speed down\r\n");
		}
		else if(CmdArr[3]==0XB5)
		{
			//SpeedRatio=CmdArr[4];
			//return SetSpeedRatio_Flag;
			CurrentSpeed = CmdArr[4];
			printf("speed set\r\n");
		}
		else if(CmdArr[3]==0XB6)
		{
			//TemperatureRatio=CmdArr[4];
			//return SetTemperatureRatio_Flag;
			Kp1 = CmdArr[4];
			printf("KP set\r\n");
		}else
		{
			BtCtlMode = 0;//退出蓝牙控制模式
			//KeyCtlMode = 0;
			AutoMode = 1;// 进入自动模式
		}
		
	}
	else
	{
		
		BtCtlMode = 0;//退出蓝牙控制模式
		//KeyCtlMode = 0;
		AutoMode = 1;// 进入自动模式
	}
}

