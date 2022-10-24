/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/

#include "main.h"
extern uint8_t Init_Flag;


/************************************************************************************************
* 函  数：void System_Init(void)
* 功  能：初始化函数
* 参  数：    
* 返回值：无 
* 备  注：本程序为STM32飞控新生比赛精简版
************************************************************************************************/
void System_Init(void)
{
	LED_Init();										//状态指示灯初始化
	NvicConfig(); 								//系统中断优先级管理（不是中断初始化）		
	Delay_Init(); 								//系统延时初始化
	USART_init(115200);						//调试串口初始化      
	IIC_GPIO_Init(); 							//模拟IIC初始化
	TIM_Init();										//系统时基初始化，TIM4作为系统时基
	MPU6050_Init();	 							//MPU6050初始化
  MOTOR_Init(); 								//电机输出初始化													
	PidParameter_init(); 					//PID参数初始化								
	GENERAL_TIM_Init();						//TIM2和TIM1初始化及其中断初始化 用于对接收机信号进行输入捕获
	
	Butterworth_Parameter_Init();
	xInit_Kalman(); //newAngle 角度
  yInit_Kalman();
	zInit_Kalman();
}

/************************************************************************************************
* 函  数：void Task_Schedule(void)
* 功  能：任务函数
* 参  数：    
* 返回值：无 
* 备  注：本程序为STM32飞控新生比赛精简版
************************************************************************************************/
void Task_Schedule(void)
{
	
	
		if(IMU_Scan) 																												//100Hz
		{
			IMU_Scan  = 0;																									//标志位清零
			Prepare_Data(); 																								//获取姿态解算所需数据
			IMUupdate(&Gyr_rad,&Acc_filt,&Att_Angle); 											//四元数姿态解算
			Control(&Att_Angle,&Gyr_rad,&RC_Control,Airplane_Enable); 			//姿态控制
			
		}
		if(LED_Scan) //10Hz
		{
			
			LED_Scan = 0;
			if( Init_Flag == 0 )//初始化过程中R灯闪烁
			{
				LEDR_H;
				LEDG_H;
				LEDB_H;
				if(loop)
				{
					loop=0;
					LEDR_H;
				}
				else
				{
					loop=1;
					LEDR_L;
				}
			}
			
			if( lock && Init_Flag == 1 )//初始化完成，飞机上锁，遥控器信号正常,G灯闪烁
			{
				LEDR_H;
				LEDG_H;
				LEDB_H;
				if(loop)
				{
					loop=0;
					LEDG_H;
				}
				else
				{
					loop=1;
					LEDG_L;
				}
			}
			if( !lock && Init_Flag == 1)//初始化完成，飞机解锁,B灯闪烁
			{
				LEDR_H;
				LEDG_H;
				LEDB_H;
				if(loop)
				{
					loop=0;

					LEDB_H;
				}
				else
				{
					loop=1;

					LEDB_L;
				}

			}
			
			
		}
		
}


