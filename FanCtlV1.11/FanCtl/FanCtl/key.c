#include "key.h"
#include "global.h"

sbit KeyRunStop = P2^0;
sbit KeyDir = P3^4;
sbit KeySpeedInc = P3^5;
sbit keySpeedDec = P2^1;

sbit keyModeCtl = P1^7;

/******************************************
* Function Name  : KeyScan
* Description    : None
* Input          : mode:0,不支持连续按;1,支持连续按;
* Output         : None
* Return         : 返回按键值
*******************************************/
void KeyScan(u16 mode)
{
	if((KeyRunStop==0||KeyDir==0||KeySpeedInc==0||keySpeedDec==0||keyModeCtl==0))
	{
		AutoMode = 0;
		KeyCtlMode = 1;//进入按键控制模式
		//printf("key scan\r\n");
		DelayMs(50); //消抖
		if(KeyRunStop==0)
			{	
				printf("key run stop\r\n");
				gStopFlag=~gStopFlag;
				//gStopFlag++;
				while(!KeyRunStop);
				return;
			}
		else if(KeyDir==0)
		{
			gDir = ~gDir;
			//gDir++;
			printf("key dir\r\n");
			while(!KeyDir);
			return;
		}
		else if(KeySpeedInc==0)
		{
			printf("key Inc\r\n");
			if(255-CurrentSpeed<25)
			{
				CurrentSpeed = 255;
			}
			else
			{
				CurrentSpeed+=SpeedInc;
			}
			while(!KeySpeedInc);
			return;
		}
		else if(keySpeedDec==0)	
		{
			printf("key Dec\r\n");
			if(CurrentSpeed<25)
			{
				CurrentSpeed=0;
			}else
			{
				CurrentSpeed-=SpeedInc;
			}
			while(!keySpeedDec);
			return;
		}else if(keyModeCtl == 0)
		{
			printf("key out\r\n");
			AutoMode = 1;
			KeyCtlMode = 0;//退出按键控制模式
			while(!keyModeCtl);
		}
	}
	
}

