#ifndef __DS18B20_H__
#define __DS18B20_H__

//������Ҫ��ͷ�ļ�
#include "STC12C5A60S2.h"   
#include "intrins.h"
#include "type.h"

//�򵥺궨��
#define uchar unsigned char
#define uint  unsigned int;

//����ds18b20��DQ����
sbit DQ=P1^5;

//��������
void Delay(unsigned char a1,b1,c1);//��ʱ����
float ReadTemperature();//��ȡ�¶�
void Init_Ds18b20(void);//��ʼ���¶ȴ�����
unsigned char ReadOneChar(void);//��һ���ֽں���
void WriteOneChar(unsigned char dat);//дһ���ֽں���

#endif //__DS18B20_H__


