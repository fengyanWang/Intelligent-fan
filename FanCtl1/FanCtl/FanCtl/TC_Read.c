#include "TC_Read.h"
#include "18b20.h"


void TC_Init(void)
{
	Init_Ds18b20();
}

void TC_Read(float *t)
{
	*t = ReadTemperature();
}

