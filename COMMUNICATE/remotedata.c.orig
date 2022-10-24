/*******************************************************************************************
* 程序版本：V1.0
* 程序日期：2020-9-20
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
*******************************************************************************************/
#include "main.h"
#include "remotedata.h"
#include "usart.h"
#include "structconfig.h"
#include "led.h"


uint8_t DataID;	//数据包ID
RC_TYPE RC_Control;

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

