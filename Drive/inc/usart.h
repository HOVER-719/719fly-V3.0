/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*                        张润
*                        杨晨阳
************************************************************************************************/
#ifndef   _USART_H
#define   _USART_H
#include "main.h"


void USART_init(uint32_t baudrate);
void usart_send(uint8_t *data,uint8_t len);

#endif

