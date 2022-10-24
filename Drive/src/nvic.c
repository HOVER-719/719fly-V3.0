/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/
#include "stm32f10x.h"

/*****************************************************************************
* 函  数：void NvicConfig(void)
* 功  能：配置工程中所有中断的优先级
* 参  数：无
* 返回值：无
* 备  注：此优先级中断不要随便更改哦
*****************************************************************************/
void NvicConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;   						//TIM4中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;   	//抢占优先级0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;   				//子优先级1
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   						//使能TIM4中断通道
	NVIC_Init(&NVIC_InitStruct);   													//中断优先级初始化函数
	
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;						//串口1中断通道  用于与上位机通信
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;   					//配置外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;   	//设置抢占优先级为0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;   				//设置子优先级为1
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   						//使能外部中断通道
	NVIC_Init(&NVIC_InitStruct);   													//中断优先级初始化函数
																
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn ;						//设置中断来源：TIM2（普通定时器多种中断共用一个服务函数，在其内部通过各自的标志位进行区分）
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;		//设置主优先级为0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;		      //设置抢占优先级为3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
																		
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_CC_IRQn ;				//设置中断来源:TIM1输入捕获（高级定时器中断服务划分更细致）
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;		//设置主优先级为0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;					//设置抢占优先级为2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;           //设置中断来源:USART3
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;   
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
}

