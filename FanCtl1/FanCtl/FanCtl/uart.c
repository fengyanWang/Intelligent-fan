#include "uart.h"
#include "intrins.h"
#include "STC12C5A60S2.h"
#include "data_parse.h"
#include "stdio.h"
#include "global.h"

#define FOSC 11059200L      //System frequency
#define BAUD 9600           //UART baudrate

sbit BlueToothState = P1^4;//蓝牙的状态显示位
sbit BlueToothEn 		= P1^5;//蓝牙的模式选择位

bit busy;
u8 gFrameCount=0;
BOOL gCmdFlag = 0;
void uartInit(void)
{
    SCON = 0x50;            //8-bit variable UART
    TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
    TH1 = TL1 = -(FOSC/12/32/BAUD); //Set auto-reload vaule
    TR1 = 1;                //Timer1 start run
    ES = 1;                 //Enable UART interrupt
    EA = 1;                 //Open master interrupt switch
}

/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4 using 1
{
    if (RI)
    {
			if(gCmdFlag==0)
			{
				CmdArr[gFrameCount]=SBUF;
				if(CmdArr[0]==0xA5)
					gFrameCount++;
				if(gFrameCount==6)
				{
					gCmdFlag = 1;
					gFrameCount = 0;
				}
		  }
      RI = 0;             //Clear receive interrupt flag
			
    }
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(u8 dat)
{
    while (busy);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    busy = 1;
    SBUF = ACC;             //Send data to UART buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString(u8 *s)
{
    while (*s)              //Check the end of the string
    {
        SendData(*s++);     //Send current char and increment string ptr
    }
}

char putchar (char dat)
{
	SendData(dat);
	return dat;
}
