#include "motor.h"
#include "STC12C5A60S2.h"
#include "global.h"

sfr PCAPWM0     =   0xf2;
sfr PCAPWM1     =   0xf3;

sbit IN1 = P2^4;
sbit IN2 = P2^5;


void motorInit(void)
{
	
    CCON = 0;                       //Initial PCA control register
                                    //PCA timer stop running
                                    //Clear CF flag
                                    //Clear all module interrupt flag
    CL = 0;                         //Reset PCA base timer
    CH = 0;
    CMOD = 0x00;                    //Set PCA timer clock source as Fosc/2
                                    //Disable PCA timer overflow interrupt
    CCAP0H = CCAP0L = 0x80;         //PWM0 port output 50% duty cycle square wave
    CCAPM0 = 0x42;                  //PCA module-0 work in 8-bit PWM mode and no PCA interrupt

    //CCAP1H = CCAP1L = 0xff;         //PWM1 port output 0% duty cycle square wave
    //PCAPWM1 = 0x03;
    //CCAPM1 = 0x42;                  //PCA module-1 work in 8-bit PWM mode and no PCA interrupt

    CR = 1;                         //PCA timer start run
}

void motorSetSpeed(u8 speed)
{
	CCAP0H = CCAP0L = 255-speed;
}

void motorSetDir(BOOL dir)// 0 反转 1正转
{
	IN1 = dir;
	IN2 = ~dir;
}

void motorStop(void)
{
	IN1=0;
	IN2=0;
}

void motorCtl(void)
{
	motorSetDir(gDir);
	if(!gStopFlag)motorStop();
	motorSetSpeed(CurrentSpeed);
}

