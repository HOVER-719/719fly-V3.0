/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/
#include "rc.h"

TIM_ICUserValueTypeDef TIM_ICUserValueStructure_1;
TIM_ICUserValueTypeDef TIM_ICUserValueStructure_2;
TIM_ICUserValueTypeDef TIM_ICUserValueStructure_3;
TIM_ICUserValueTypeDef TIM_ICUserValueStructure_4;
TIM_ICUserValueTypeDef TIM_ICUserValueStructure_5;
RC_TYPE RC_Control;

//GPIO初始化
static void GENERAL_TIM_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM_GPIO_CLK ,ENABLE);
	GPIO_InitStructure.GPIO_Pin 	= 	GENERAL_TIM_CH1_PIN|GENERAL_TIM_CH2_PIN|GENERAL_TIM_CH3_PIN|GENERAL_TIM_CH4_PIN|GENERAL_TIM_CH5_PIN;
	GPIO_InitStructure.GPIO_Mode 	= 	GPIO_Mode_IN_FLOATING;
	GPIO_Init(GENERAL_TIM_PORT ,&GPIO_InitStructure);
}


//定时器初始化
static void GENERAL_TIM_Mode_Config(void)
{
	GENERAL_TIM_APB1Clock_FUN(GENERAL_TIM2_CLK ,ENABLE);												//开启定时器时钟，内部时钟CK_INT=72M
	GENERAL_TIM_APB2Clock_FUN(GENERAL_TIM1_CLK ,ENABLE);												//开启定时器时钟，内部时钟CK_INT=72M
	//时基结构体初始化
	    //TIM2
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;														
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period ;										//自动重装载寄存器值，累计TIM_Period+1个频率后产生一个更新或中断
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM_Prescaler;							//驱动CNT计数器时钟=Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;										//时钟分频
	TIM_TimeBaseStructure.TIM_CounterMode= TIM_CounterMode_Up;								//向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;													//重复计数器的值
	TIM_TimeBaseInit(TIM2 ,&TIM_TimeBaseStructure);										//初始化定时器
			//TIM1
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;														
	TIM_TimeBaseStructure2.TIM_Period = GENERAL_TIM_Period ;										//自动重装载寄存器值，累计TIM_Period+1个频率后产生一个更新或中断
	TIM_TimeBaseStructure2.TIM_Prescaler = GENERAL_TIM_Prescaler;							//驱动CNT计数器时钟=Fck_int/(psc+1)
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;										//时钟分频
	TIM_TimeBaseStructure2.TIM_CounterMode= TIM_CounterMode_Up;								//向上计数模式
	TIM_TimeBaseStructure2.TIM_RepetitionCounter = 0;													//重复计数器的值
	TIM_TimeBaseInit(TIM1 ,&TIM_TimeBaseStructure2);										//初始化定时器
	
	//输入捕获    此处未配置输入捕获的触发方式（上升沿捕获/下降沿捕获），因为需要在中断服务函数里进行翻转（上升沿/下降沿触发输入捕获->输入捕获触发中断）
		//TIM2CH1
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_1;									//配置输入捕获的通道
	TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_START_ICPolarity ;				//输入捕获信号极性
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;						//输入通道和捕获通道映射关系
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;											//输入的被捕获信号的分频系数
	TIM_ICInitStructure.TIM_ICFilter = 0;																			//输入的被捕获信号的滤波系数
	TIM_ICInit(TIM2 , &TIM_ICInitStructure);														//定时器输入捕获初始化
		//TIM2CH2
	TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_2;									//配置输入捕获的通道
	TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_START_ICPolarity ;				//输入捕获信号极性
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;						//输入通道和捕获通道映射关系
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;											//输入的被捕获信号的分频系数
	TIM_ICInitStructure.TIM_ICFilter = 0;																			//输入的被捕获信号的滤波系数
	TIM_ICInit(TIM2 , &TIM_ICInitStructure);														//定时器输入捕获初始化
		//TIM2CH3
	TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_3;									//配置输入捕获的通道
	TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_START_ICPolarity ;				//输入捕获信号极性
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;						//输入通道和捕获通道映射关系
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;											//输入的被捕获信号的分频系数
	TIM_ICInitStructure.TIM_ICFilter = 0;																			//输入的被捕获信号的滤波系数
	TIM_ICInit(TIM2 , &TIM_ICInitStructure);														//定时器输入捕获初始化
		//TIM2CH4
	TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_4;									//配置输入捕获的通道
	TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_START_ICPolarity ;				//输入捕获信号极性
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;						//输入通道和捕获通道映射关系
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;											//输入的被捕获信号的分频系数
	TIM_ICInitStructure.TIM_ICFilter = 0;																			//输入的被捕获信号的滤波系数
	TIM_ICInit(TIM2 , &TIM_ICInitStructure);														//定时器输入捕获初始化
		//TIM1CH1
	TIM_ICInitStructure.TIM_Channel = GENERAL_TIM_CHANNEL_1;									//配置输入捕获的通道
	TIM_ICInitStructure.TIM_ICPolarity = GENERAL_TIM_START_ICPolarity ;				//输入捕获信号极性
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;						//输入通道和捕获通道映射关系
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;											//输入的被捕获信号的分频系数
	TIM_ICInitStructure.TIM_ICFilter = 0;																			//输入的被捕获信号的滤波系数
	TIM_ICInit(TIM1 , &TIM_ICInitStructure);														//定时器输入捕获初始化
	
	
	
	//清除更新和捕获中断标志位
			//TIM2
	TIM_ClearFlag(TIM2 , TIM_FLAG_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4 );					
			//TIM1
	TIM_ClearFlag(TIM1 , TIM_FLAG_Update|TIM_IT_CC1 );					
	//开启更新和捕获中断
			//TIM2
	TIM_ITConfig(TIM2 ,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4 ,ENABLE);			
			//TIM1
	TIM_ITConfig(TIM1 ,TIM_IT_Update|TIM_IT_CC1,ENABLE);			
	//使能计数器
			//TIM2
	TIM_Cmd(TIM2 ,ENABLE);																						
			//TIM1
	TIM_Cmd(TIM1 ,ENABLE);																							
}


void GENERAL_TIM_Init(void)
{
	GENERAL_TIM_GPIO_Config();
	GENERAL_TIM_Mode_Config();
}

void Remote_Data_ReceiveAnalysis(void)
{
	int16_t the1;
	int16_t the2;
	int16_t the3;
	int16_t the4;
	
			//if((TIM_ICUserValueStructure_1.Capture_CcrValue_b-TIM_ICUserValueStructure_1.Capture_CcrValue_a)<2100&&(TIM_ICUserValueStructure_1.Capture_CcrValue_b-TIM_ICUserValueStructure_1.Capture_CcrValue_a)>900)
			the1=TIM_ICUserValueStructure_1.Capture_CcrValue_b-TIM_ICUserValueStructure_1.Capture_CcrValue_a;
			if(the1<0)the1+=65536;
			if(the1<2100&&the1>900)
			RC_Control.ROLL = the1;
			
			//if((TIM_ICUserValueStructure_2.Capture_CcrValue_b-TIM_ICUserValueStructure_2.Capture_CcrValue_a)<2100&&(TIM_ICUserValueStructure_2.Capture_CcrValue_b-TIM_ICUserValueStructure_2.Capture_CcrValue_a)>900)
			the2=TIM_ICUserValueStructure_2.Capture_CcrValue_b-TIM_ICUserValueStructure_2.Capture_CcrValue_a;
			if(the2<0)the2+=65536;
			if(the2<2100&&the2>900)
			RC_Control.PITCH = the2;
			
			//if((TIM_ICUserValueStructure_3.Capture_CcrValue_b-TIM_ICUserValueStructure_3.Capture_CcrValue_a)<2100&&(TIM_ICUserValueStructure_3.Capture_CcrValue_b-TIM_ICUserValueStructure_3.Capture_CcrValue_a)>900)
	   	the3=TIM_ICUserValueStructure_3.Capture_CcrValue_b-TIM_ICUserValueStructure_3.Capture_CcrValue_a;
			if(the3<0)the3+=65536;
			if(the3<2100&&the3>900)
			RC_Control.THROTTLE = the3;
			
			//if((TIM_ICUserValueStructure_4.Capture_CcrValue_b-TIM_ICUserValueStructure_4.Capture_CcrValue_a)<2100&& (TIM_ICUserValueStructure_4.Capture_CcrValue_b-TIM_ICUserValueStructure_4.Capture_CcrValue_a)>900)
			the4=TIM_ICUserValueStructure_4.Capture_CcrValue_b-TIM_ICUserValueStructure_4.Capture_CcrValue_a;
			if(the4<0)the4+=65536;
			if(the4<2100&&the4>900)
			RC_Control.YAW = the4;
}
