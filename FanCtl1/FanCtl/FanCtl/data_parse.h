#ifndef DATA_PARSE_H
#define DATA_PARSE_H
#include "type.h"

//�򵥺궨��
//#define unsigned char uchar
//#define unsigned int uint

//����ĺ궨��
#define Run_Flag 										1 //���������־
#define Stop_Flag 									2 //��ͣ�����־
#define PositiveDir_Flag 						3 //�������������־
#define NegativeDir_Flag 						4 //�������������־
#define SpeedInc_Flag 							5 //���������־
#define SpeedDec_Flag 							6 //���������־
#define SetSpeedRatio_Flag 					7 //����ת�ٱ������־
#define SetTemperatureRatio_Flag 		8 //�����²�������־

extern u8 CmdArr[8];
//�����������������
void CmdParse(void);

#endif //DATA_PARSE_H

