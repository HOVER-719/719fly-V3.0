/************************************************************************************************
* 程序版本：V3.0
* 程序日期：2022-9-6
* 程序作者：719飞行器实验室：
*                        张润
*                        杨晨阳
*                        张天鹏
************************************************************************************************/
#ifndef   _LED_H
#define   _LED_H

#include "main.h"

#define LEDR_H GPIOB->BSRR |= GPIO_Pin_12 //配置LED引脚为 高电平
#define LEDR_L GPIOB->BRR  |= GPIO_Pin_12 //配置LED引脚为 低电平

#define LEDG_H GPIOB->BSRR |= GPIO_Pin_13 //配置LED引脚为 高电平
#define LEDG_L GPIOB->BRR  |= GPIO_Pin_13 //配置LED引脚为 低电平

#define LEDB_H GPIOB->BSRR |= GPIO_Pin_14 //配置LED引脚为 高电平
#define LEDB_L GPIOB->BRR  |= GPIO_Pin_14 //配置LED引脚为 低电平

void LED_Init(void);
void LEDR_1(void);
void LEDR_2(void);
void LEDR_3(void);

void LEDG_1(void);
void LEDG_2(void);
void LEDG_3(void);

void LEDB_1(void);
void LEDB_2(void);
void LEDB_3(void);

void led_task(void);
void led_test(void);

#endif
