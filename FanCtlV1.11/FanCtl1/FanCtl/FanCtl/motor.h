#ifndef MOTOR_H
#define MOTOR_H
#include "type.h"

void motorInit(void);
void motorSetSpeed(u8 speed);
void motorSetDir(BOOL dir);
void motorStop(void);
void motorCtl(void);
#endif //MOTOR_H