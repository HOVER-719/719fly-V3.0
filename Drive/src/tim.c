/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/
#include "stm32f10x.h"


/*****************************************************************************
* 函  数：void TIM_Init(void)
* 功  能：TIM4初始化为1ms计数一次,系统时基  
* 参  数：无
* 返回值：无
* 备  注：更新中断时间 Tout = (ARR+1)*(PSC+1)/CK_INT
*****************************************************************************/
void TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   				//定义定时器结构体变量
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);   		//使能TIM4的时钟
	
	TIM_TimeBaseInitStruct.TIM_Period=1000-1;   							//设置自动重装载的周期值
	TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;   							//设置预分频值
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;   						//设置时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);   				//定时器初始化函数
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);   								//TIM4中断使能
	
	TIM_Cmd(TIM4,ENABLE);   																	//TIM4使能
}

