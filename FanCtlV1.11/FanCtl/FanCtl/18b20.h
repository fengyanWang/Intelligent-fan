#ifndef __DS18B20_H__
#define __DS18B20_H__

//包含必要的头文件
#include "STC12C5A60S2.h"   
#include "intrins.h"
#include "type.h"

//简单宏定义
#define uchar unsigned char
#define uint  unsigned int;

//定义ds18b20的DQ引脚
sbit DQ=P1^5;

//函数声明
void Delay(unsigned char a1,b1,c1);//延时函数
float ReadTemperature();//获取温度
void Init_Ds18b20(void);//初始化温度传感器
unsigned char ReadOneChar(void);//读一个字节函数
void WriteOneChar(unsigned char dat);//写一个字节函数

#endif //__DS18B20_H__


