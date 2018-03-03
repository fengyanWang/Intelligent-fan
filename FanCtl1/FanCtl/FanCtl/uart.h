#ifndef UART_H
#define UART_H
#include "type.h"

void SendData(u8 dat);
void SendString(u8 *s);
void uartInit(void);

#endif //UART_H