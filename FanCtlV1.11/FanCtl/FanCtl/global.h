#ifndef GLOBAL_H
#define GLOBAL_H

extern u16 Kp1;		//定义温差比例系数
extern u8 CurrentSpeed; //定义当前速度
extern u8 SpeedInc; //速度增量
extern BOOL gDir;	//方向
extern BOOL gStopFlag; //停止标志位0停止1运行

extern BOOL AutoMode; //自动模式
extern BOOL KeyCtlMode;//按键控制模式
extern BOOL BtCtlMode;//蓝牙控制模式
extern u8 gFrameCount;
extern BOOL gCmdFlag;
#endif //GLOBAL_H

