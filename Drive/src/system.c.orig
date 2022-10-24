/************************************************************************************************
* ����汾��V2.1
* �������ڣ�2021-12-8
* �������ߣ�719������ʵ���ң� 
*						����
*						���
************************************************************************************************/

#include "main.h"
extern uint8_t Init_Flag;


/************************************************************************************************
* ��  ����void System_Init(void)
* ��  �ܣ���ʼ������
* ��  ����    
* ����ֵ���� 
* ��  ע��������ΪSTM32�ɿ��������������
************************************************************************************************/
void System_Init(void)
{
	LED_Init();										//״ָ̬ʾ�Ƴ�ʼ��
	NvicConfig(); 								//ϵͳ�ж����ȼ������������жϳ�ʼ����		
	Delay_Init(); 								//ϵͳ��ʱ��ʼ��
	USART_init(115200);						//���Դ��ڳ�ʼ��      
	IIC_GPIO_Init(); 							//ģ��IIC��ʼ��
	TIM_Init();										//ϵͳʱ����ʼ����TIM4��Ϊϵͳʱ��
	MPU6050_Init();	 							//MPU6050��ʼ��
  MOTOR_Init(); 								//��������ʼ��													
	PidParameter_init(); 					//PID������ʼ��								
	GENERAL_TIM_Init();						//TIM2��TIM1��ʼ�������жϳ�ʼ�� ���ڶԽ��ջ��źŽ������벶��
	
	Butterworth_Parameter_Init();
	xInit_Kalman(); //newAngle �Ƕ�
  yInit_Kalman();
	zInit_Kalman();
}

/************************************************************************************************
* ��  ����void Task_Schedule(void)
* ��  �ܣ�������
* ��  ����    
* ����ֵ���� 
* ��  ע��������ΪSTM32�ɿ��������������
************************************************************************************************/
void Task_Schedule(void)
{
	
	
		if(IMU_Scan) 																												//100Hz
		{
			IMU_Scan  = 0;																									//��־λ����
			Prepare_Data(); 																								//��ȡ��̬������������
			IMUupdate(&Gyr_rad,&Acc_filt,&Att_Angle); 											//��Ԫ����̬����
			Control(&Att_Angle,&Gyr_rad,&RC_Control,Airplane_Enable); 			//��̬����
			
		}
		if(LED_Scan) //10Hz
		{
			LED_Scan = 0;
			if( Init_Flag == 0 )//��ʼ��������R����˸
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
			
			if( lock && Init_Flag == 1 )//��ʼ����ɣ��ɻ�������ң�����ź�����,G����˸
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
			if( !lock && Init_Flag == 1)//��ʼ����ɣ��ɻ�����,B����˸
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


