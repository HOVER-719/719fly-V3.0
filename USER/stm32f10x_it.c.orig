/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/

#include "stm32f10x.h"
#include "delay.h"
#include "main.h"
#include "stdio.h"
#include "led.h"
#include "remotedata.h"
#include "rc.h"
#include "string.h"

//周期性任务的执行标志位
uint8_t LED_Scan = 0;
uint8_t IMU_Scan = 0;
uint8_t MPU_Scan = 0;
uint8_t IRQ_Scan = 0;
uint8_t Batt_Scan = 0;
uint8_t muartWaitFlag = 0;
uint8_t lock = 1;
uint8_t Init_Flag = 0;
uint8_t Init_Time = 0;

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_1;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_2;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_3;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_4;
extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure_5;

extern uint8_t MPU6050_OffSet_Flag;

/****************************************************************************************************
* 函  数: void USART1_IRQHandler(void)
* 功  能: USART1中断函数
* 参  数: 无
* 返回值: 无
* 备  注: 
****************************************************************************************************/
void USART1_IRQHandler(void)
{
	uint8_t clear = clear; 																				//定义这个变量是针对编译出现“没有用到这个变量”的警告提示
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 				//接收中断
	{ 
		
	}
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET) 	//空闲中断
	{
		clear = USART1->SR; 																				//读SR寄存器
		clear = USART1->DR; 																				//读DR寄存器（先读SR,再度DR,就是为了清除IDIE中断）
		
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

/****************************************************************************************************
* 函  数: void TIM4_IRQHandler(void) 
* 功  能: TIM4定时器中断，1ms进一次中断也就是1000Hz
* 参  数: 无
* 返回值: 无
* 备  注: 此函数是整个程序的运行时基，不同的中断时间对应不同频率；
*         对于一些计算对调用时间要求比较严格时可用此方法；
*         扫描频率 = 1000Hz/分频系数；
****************************************************************************************************/
void TIM4_IRQHandler(void)   //TIM4中断服务函数
{
	static uint16_t ms2 = 0,ms5 = 0,ms10 = 0,ms20 = 0,ms100 = 0,ms200 = 0,ms400 = 0; //分频系数
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)	//判断是否进入TIM更新中断
	{
		ms2++;
		ms5++;
		ms10++;	
		ms20++;	
		ms100++;
		ms200++;
		ms400++;  																//这里的数字决定了周期性任务在
		if(ms2 >= 2)															//500Hz
		{
			ms2 = 0;
		}
		if(ms5 >= 5)															//200Hz
		{
			ms5 = 0;
			MPU_Scan = 1;
		}
		if(ms10 >= 10)														//100Hz
		{
			ms10 = 0;
			IMU_Scan = 1;
			
		}
		if(ms20 >= 20)														//50Hz
		{
			ms20 = 0;
		}
		if(ms100 >= 100)													//10Hz
		{
				ms100 = 0;
			
				LED_Scan = 1;
			
				if( Init_Flag == 0 )
				{
					Init_Time ++;
				}
				
				if( Init_Time >= 100 && Att_Angle.pit < 0.3 && Att_Angle.rol <0.3 )////初始化等待时间结束，且IMU输出角度在正常范围内
				{
					Init_Time = 0;
					Init_Flag = 1;//初始化标志位为1，开始打印
				}
				
				if( Init_Flag == 1 )
				{
//					printf("PIT = %5.2f",Att_Angle.pit);
//					printf("ROL = %5.2f",Att_Angle.rol);
//					printf("YAW = %5.2f\r\n",Att_Angle.yaw);
//					printf("%f,%f,%f\r\n",PID_ROL_Rate.Pout,PID_ROL_Rate.Iout,PID_ROL_Rate.Dout);
//          打印PID在ROLL、PITCH、YAW三个轴上的作用
				}
				else
				{
					printf("Loading\r\n");
				}
				
		}
		
		if(ms200 >= 200)													//5Hz
		{
			ms200 = 0;

		}
		if(ms400 >= 400)													//2.5Hz
		{
			ms400 = 0;
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	//清除TIM4更新中断
}


/*****************************************************************************
* 函  数：void TIM2_IRQHandler (void)
* 功  能：TIM2的中断服务函数
* 参  数：无
* 返回值：无
* 备  注:
*****************************************************************************/
void TIM2_IRQHandler (void)										//TIM2的中断服务函数  计数器溢出，4个输入捕获都指向该中断函数，用各自的标志位进行区分
{
	
	if(TIM_GetITStatus (TIM2 ,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit (TIM2 ,TIM_FLAG_Update);
	}	
	
	if(TIM_GetITStatus (TIM2 ,TIM_IT_CC1) != RESET)
	{
		if(TIM_ICUserValueStructure_1.Capture_StartFlag ==0)
		{
			TIM_ICUserValueStructure_1.Capture_CcrValue_a = TIM_GetCapture1 (TIM2 );
			TIM_OC1PolarityConfig(TIM2 , TIM_ICPolarity_Falling);
			TIM_ICUserValueStructure_1.Capture_StartFlag = 1;
		}
		else
		{
			TIM_ICUserValueStructure_1.Capture_CcrValue_b = TIM_GetCapture1 (TIM2 );
			TIM_OC1PolarityConfig(TIM2 ,TIM_ICPolarity_Rising);
			TIM_ICUserValueStructure_1.Capture_StartFlag = 0;
			TIM_ICUserValueStructure_1.Capture_FinishFlag = 1;
		}
		TIM_ClearITPendingBit (TIM2 ,TIM_IT_CC1 );
	}
	
	if(TIM_GetITStatus (TIM2 ,TIM_IT_CC2) != RESET)
	{
		if(TIM_ICUserValueStructure_2.Capture_StartFlag ==0)
		{
			TIM_ICUserValueStructure_2.Capture_CcrValue_a = TIM_GetCapture2 (TIM2 );
			TIM_OC2PolarityConfig(TIM2 , TIM_ICPolarity_Falling);
			TIM_ICUserValueStructure_2.Capture_StartFlag = 1;
		}
		else
		{
			TIM_ICUserValueStructure_2.Capture_CcrValue_b = TIM_GetCapture2 (TIM2 );
			TIM_OC2PolarityConfig(TIM2 ,TIM_ICPolarity_Rising);
			TIM_ICUserValueStructure_2.Capture_StartFlag = 0;
			TIM_ICUserValueStructure_2.Capture_FinishFlag = 1;
		}
		TIM_ClearITPendingBit (TIM2 ,TIM_IT_CC2 );
	}
	
	if(TIM_GetITStatus (TIM2 ,TIM_IT_CC3) != RESET)
	{
		if(TIM_ICUserValueStructure_3.Capture_StartFlag ==0)
		{
			TIM_ICUserValueStructure_3.Capture_CcrValue_a = TIM_GetCapture3 (TIM2 );
			TIM_OC3PolarityConfig(TIM2 , TIM_ICPolarity_Falling);
			TIM_ICUserValueStructure_3.Capture_StartFlag = 1;
		}
		else
		{
			TIM_ICUserValueStructure_3.Capture_CcrValue_b = TIM_GetCapture3 (TIM2 );
			TIM_OC3PolarityConfig(TIM2 ,TIM_ICPolarity_Rising);
			TIM_ICUserValueStructure_3.Capture_StartFlag = 0;
			TIM_ICUserValueStructure_3.Capture_FinishFlag = 1;
		}
		TIM_ClearITPendingBit (TIM2 ,TIM_IT_CC3 );
	}
	if(TIM_GetITStatus (TIM2 ,TIM_IT_CC4) != RESET)
	{
		if(TIM_ICUserValueStructure_4.Capture_StartFlag ==0)
		{
			TIM_ICUserValueStructure_4.Capture_CcrValue_a = TIM_GetCapture4 (TIM2 );
			TIM_OC4PolarityConfig(TIM2 , TIM_ICPolarity_Falling);
			TIM_ICUserValueStructure_4.Capture_StartFlag = 1;
		}
		
		else
		{
			TIM_ICUserValueStructure_4.Capture_CcrValue_b = TIM_GetCapture4 (TIM2 );
			TIM_OC4PolarityConfig(TIM2 ,TIM_ICPolarity_Rising);
			TIM_ICUserValueStructure_4.Capture_StartFlag = 0;
			TIM_ICUserValueStructure_4.Capture_FinishFlag = 1;
		}
		TIM_ClearITPendingBit (TIM2 ,TIM_IT_CC4 );
	}
	Remote_Data_ReceiveAnalysis();																		//计算脉宽并将其存入RC_Control，由于有4个所以封成了一个函数以求简洁
}

/*****************************************************************************
* 函  数：void TIM1_CC_IRQHandler (void)
* 功  能：TIM1的中断服务函数
* 参  数：无
* 返回值：无
* 备  注:
*****************************************************************************/
void TIM1_CC_IRQHandler (void)																																												//TIM1输入捕获中断服务函数  由于是高级定时器所以中断服务函数划分比普通定时器（例如上面的TIM4）细致
{
	
if(TIM_GetITStatus (TIM1 ,TIM_IT_CC1) != RESET)
	{
		if(TIM_ICUserValueStructure_5.Capture_StartFlag ==0)
		{
			TIM_ICUserValueStructure_5.Capture_CcrValue_a = TIM_GetCapture1 (TIM1 );
			TIM_ICUserValueStructure_5.Capture_Period = 0;
			TIM_OC1PolarityConfig(TIM1 , TIM_ICPolarity_Falling);
			TIM_ICUserValueStructure_5.Capture_StartFlag = 1;
		}
		else
		{
			TIM_ICUserValueStructure_5.Capture_CcrValue_b = TIM_GetCapture1 (TIM1 );
			TIM_OC1PolarityConfig(TIM1 ,TIM_ICPolarity_Rising);
			TIM_ICUserValueStructure_5.Capture_StartFlag = 0;
			TIM_ICUserValueStructure_5.Capture_FinishFlag = 1;
		}
		TIM_ClearITPendingBit (TIM1 ,TIM_IT_CC1 );
	}
	
	if((TIM_ICUserValueStructure_5.Capture_CcrValue_b-TIM_ICUserValueStructure_5.Capture_CcrValue_a)<2100&& (TIM_ICUserValueStructure_5.Capture_CcrValue_b-TIM_ICUserValueStructure_5.Capture_CcrValue_a)>900)
			RC_Control.BUTTON = TIM_ICUserValueStructure_5.Capture_CcrValue_b-TIM_ICUserValueStructure_5.Capture_CcrValue_a;//计算脉宽并将其存入RC_Control？、	    printf("%d\r\n",RC_Control.BUTTON);

}



