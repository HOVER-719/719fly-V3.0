/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/
#ifndef   _RC_H
#define   _RC_H
#include "stm32f10x_tim.h"
#include "main.h"
//通用定时器参数定义TIM2

#define GENERAL_TIM2        									TIM2
#define GENERAL_TIM1        									TIM1
#define GENERAL_TIM_APB1Clock_FUN  					RCC_APB1PeriphClockCmd
#define GENERAL_TIM_APB2Clock_FUN  					RCC_APB2PeriphClockCmd
#define GENERAL_TIM2_CLK  									RCC_APB1Periph_TIM2
#define GENERAL_TIM1_CLK  									RCC_APB2Periph_TIM1
#define GENERAL_TIM_Period 									0XFFFF
#define GENERAL_TIM_Prescaler 							(72-1)

//TIM输入捕获通道GPIO宏定义

#define GENERAL_TIM_GPIO_CLK 								RCC_APB2Periph_GPIOA
#define GENERAL_TIM_PORT 										GPIOA
#define GENERAL_TIM_CH1_PIN	 								GPIO_Pin_0
#define GENERAL_TIM_CH2_PIN 								GPIO_Pin_1
#define GENERAL_TIM_CH3_PIN 								GPIO_Pin_2
#define GENERAL_TIM_CH4_PIN 								GPIO_Pin_3
#define GENERAL_TIM_CH5_PIN 								GPIO_Pin_8
#define GENERAL_TIM_CHANNEL_1 							TIM_Channel_1
#define GENERAL_TIM_CHANNEL_2 							TIM_Channel_2
#define GENERAL_TIM_CHANNEL_3								TIM_Channel_3
#define GENERAL_TIM_CHANNEL_4 							TIM_Channel_4


//中断宏定义

#define GENERAL_TIM_IT_CC1 									TIM_IT_CC1
#define GENERAL_TIM_IT_CC2 									TIM_IT_CC2
#define GENERAL_TIM_IT_CC3 									TIM_IT_CC3
#define GENERAL_TIM_IT_CC4 									TIM_IT_CC4
#define GENERAL_TIM2_IRQ 										TIM2_IRQn
#define GENERAL_TIM1_IRQ 										TIM1_CC_IRQn
#define GENERAL_TIM2_INT_FUN 								TIM2_IRQHandler
#define GENERAL_TIM1_INT_FUN 								TIM1_CC_IRQHandler


//获取捕获寄存器值函数宏定义

#define GENERAL_TIM_GetCapture1_FUN 				TIM_GetCapture1

#define GENERAL_TIM_GetCapture2_FUN TIM_GetCapture2
#define GENERAL_TIM_GetCapture3_FUN TIM_GetCapture3
#define GENERAL_TIM_GetCapture4_FUN TIM_GetCapture4

//捕获信号极性函数宏定义

#define GENERAL_TIM_OC1PolarityConfig_FUN 	TIM_OC1PolarityConfig

#define GENERAL_TIM_OC2PolarityConfig_FUN TIM_OC2PolarityConfig
#define GENERAL_TIM_OC3PolarityConfig_FUN TIM_OC3PolarityConfig
#define GENERAL_TIM_OC4PolarityConfig_FUN TIM_OC4PolarityConfig

//测量起始和结束边沿

#define GENERAL_TIM_START_ICPolarity 				TIM_ICPolarity_Rising
#define GENERAL_TIM_END_ICPolarity 					TIM_ICPolarity_Falling


typedef struct
{
	uint8_t 	Capture_FinishFlag;
	uint8_t 	Capture_StartFlag;
	uint16_t 	Capture_CcrValue_a;
	uint16_t 	Capture_CcrValue_b;
	uint16_t 	Capture_Period;
}TIM_ICUserValueTypeDef;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_1;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_2;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_3;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_4;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_5;



static void GENERAL_TIM_GPIO_Config(void);
static void GENERAL_TIM_Mode_Config(void);
void Remote_Data_ReceiveAnalysis(void);
void GENERAL_TIM_INT_FUN (void);
void GENERAL_TIM_Init(void);



#endif
