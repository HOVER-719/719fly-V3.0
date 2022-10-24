/*******************************************************************************************
* 程序版本：V1.0
* 程序日期：2020-9-20
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
*******************************************************************************************/
#include "stm32f10x.h"
#include "exit.h"
#include "delay.h"
#include "stdio.h"

/****************************************************************************************************
* 函  数: void Exit_Init(void)
* 功  能: 配置与SI24R1的IRQ相连的IO
* 参  数: 无
* 返回值：无
* 备  注: 无
****************************************************************************************************/
void Exit_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //定义GPIO结构体变量
	EXTI_InitTypeDef EXTI_InitStruct;	//定义外部中断结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);   //使能GPIOB的时钟并开启复用时钟
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);   //PB2中断线映射
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;   //配置GPIO第2引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;   //配置GPIO为上拉输入
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   //配置GPIO速率
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //GPIO初始化函数
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line2;   //中断线2
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;   //外部中断模式
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //下降沿触发
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;   //中断线使能
	EXTI_Init(&EXTI_InitStruct);   //外部中断初始化函数
	
}

