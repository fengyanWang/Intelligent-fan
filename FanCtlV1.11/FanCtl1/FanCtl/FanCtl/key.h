#ifndef KEY_H
#define KEY_H

#include "STC12C5A60S2.h"
#include "delay.h"
#include "type.h"

//�򵥺궨��
#define KeyRunStop_PRES		1		//KeyRunStop  
#define KeyDir_PRES		  	2		//KeyDir 
#define KeySpeedInc_PRES	3		//KeySpeedInc
#define keySpeedDec_PRES	4		//keySpeedDec

//#define unsigned int uint

//����ɨ�躯��
void KeyScan(u16 mode);

#endif //KEY_H

