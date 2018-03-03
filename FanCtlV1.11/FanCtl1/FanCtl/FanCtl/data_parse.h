#ifndef DATA_PARSE_H
#define DATA_PARSE_H
#include "type.h"

//简单宏定义
//#define unsigned char uchar
//#define unsigned int uint

//命令的宏定义
#define Run_Flag 										1 //启动命令标志
#define Stop_Flag 									2 //暂停命令标志
#define PositiveDir_Flag 						3 //正向运行命令标志
#define NegativeDir_Flag 						4 //反向运行命令标志
#define SpeedInc_Flag 							5 //加速命令标志
#define SpeedDec_Flag 							6 //减速命令标志
#define SetSpeedRatio_Flag 					7 //设置转速比命令标志
#define SetTemperatureRatio_Flag 		8 //设置温差比命令标志

extern u8 CmdArr[8];
//解析蓝牙命令函数申明
void CmdParse(void);

#endif //DATA_PARSE_H

