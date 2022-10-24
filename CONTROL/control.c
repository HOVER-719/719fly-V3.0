/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/

#include "control.h"

//角度环PID 
PID_TYPE PID_ROL_Angle;
PID_TYPE PID_PIT_Angle;
PID_TYPE PID_YAW_Angle;
//角速度环PID 
PID_TYPE PID_ROL_Rate;
PID_TYPE PID_PIT_Rate;
PID_TYPE PID_YAW_Rate;


float Pre_THROTTLE,THROTTLE;
float Moto_PWM_1=0.0f,Moto_PWM_2=0.0f,Moto_PWM_3=0.0f,Moto_PWM_4=0.0f;
uint8_t SI24R1_Controlflag = 1 , Airplane_Enable , RC_middle = 1 , RC_middle_num ;

float RC_ROLL_mid=0,RC_PITCH_mid=0,RC_YAW_mid=0;

/******************************************************************************************
*函  数：void Control(FLOAT_ANGLE *att_in,FLOAT_XYZ *gyr_in, RC_TYPE *rc_in, uint8_t armed)
*功  能：姿态控制,角度环控制和角速度环控制
*参  数：att_in：测量值
*        gry_in: MPU6050读取的角速度值
*        rc_in : 遥控器设定值
*        armed记录命令
*返回值：无
*备  注：机头与电机示意图	
					 机头(Y+)
					   
				  M1    ↑    M2
					\   |   /
					 \  |  /
					  \ | /
			    ————————+————————>X+	
					  / | \
					 /  |  \
					/   |   \
				  M4    |    M3

	
	1. M1 M3电机逆时针旋转，M2 M4电机顺时针旋转
	2. X:是MPU6050的 X 轴，Y:是MPU6050的 Y 轴，Z轴正方向垂直 X-Y 面，竖直向上
	3. 绕 X 轴旋转为PITCH 角 
	   绕 Y 轴旋转为 ROLL 角 
	   绕 Z 轴旋转为 YAW  角
	4. 自己DIY时进行动力分配可以一个轴一个轴的分配，切勿三个轴同时分配。
*******************************************************************************************/
void Control(FLOAT_ANGLE *att_in,FLOAT_XYZ *gyr_in, RC_TYPE *rc_in, uint8_t armed)
{
	
	if(RC_middle==1)
	{
		Delay_ms(500);//等待输入捕获进入中断
	for(RC_middle_num=0;RC_middle_num<10;RC_middle_num++)
		{
			RC_ROLL_mid+=(float)RC_Control.ROLL;
			RC_PITCH_mid+=(float)RC_Control.PITCH;
			RC_YAW_mid+=(float)RC_Control.YAW;
		}
		RC_ROLL_mid/=10.0;
		RC_PITCH_mid/=10.0;
		RC_YAW_mid/=10.0;
		RC_middle=0;
	}
	
	FLOAT_ANGLE Measure_Angle,Target_Angle;
	Measure_Angle.rol = att_in->rol; 
	Measure_Angle.pit = att_in->pit; 
	Measure_Angle.yaw = att_in->yaw; 
	Target_Angle.rol = (float)((RC_ROLL_mid-rc_in->ROLL)/10.0f);
	Target_Angle.pit = (float)((RC_PITCH_mid-rc_in->PITCH)/10.0f);
	Target_Angle.yaw = (float)((RC_YAW_mid-rc_in->YAW)/10.0f); 

	//角度环
	PID_Postion_Cal(&PID_ROL_Angle,Target_Angle.rol,Measure_Angle.rol);//ROLL角度环PID （输入角度 输出角速度）
	PID_Postion_Cal(&PID_PIT_Angle,Target_Angle.pit,Measure_Angle.pit);//PITH角度环PID （输入角度 输出角速度）
	
	
//	OLED_ShowString(6,2,"Iou",16);
//	OLED_Showdecimal(46,2,PID_ROL_Angle.Dout,2,1,16);
//	OLED_ShowString(6,4,"Tar",16);
//	OLED_Showdecimal(46,4,PID_ROL_Angle.OutPut,3,1,16);
	
	//角速度环
	PID_Postion_Cal(&PID_ROL_Rate,PID_ROL_Angle.OutPut,(gyr_in->Y*RadtoDeg)); 					//ROLL角速度环PID （输入角度环的输出，输出电机控制量）
	PID_Postion_Cal(&PID_PIT_Rate,PID_PIT_Angle.OutPut,-(gyr_in->X*RadtoDeg)); 					//PITH角速度环PID （输入角度环的输出，输出电机控制量）
	PID_Postion_Cal(&PID_YAW_Rate,Target_Angle.yaw*PID_YAW_Angle.P,gyr_in->Z*RadtoDeg); //YAW角速度环PID （输入角度，输出电机控制量）
	
//	OLED_ShowString(6,6,"Mot",16);
//	OLED_Showdecimal(46,6,PID_ROL_Rate.OutPut,5,1,16);
	

//动力分配（自己DIY时动力分配一定要好好研究，动力分配搞错飞机肯定飞不起来）
//动力分配可以使飞控适配不同类型的飞行器，如四轴、六轴、八轴等
//如果无法解锁，可设法打印 RC_Control.BUTTON 的值，并将解锁范围设为包含解锁状态下 RC_Control.BUTTON 的区间
//对于富斯I6遥控器，2档开关拨至高位为1000，拨至低位为2000，3挡开关拨至高位为1000，拨至中位为1500，拨至低位为2000

	if( RC_Control.BUTTON < 1400 || RC_Control.BUTTON > 2100 )
	{
		lock= 1 ;
		Moto_PWM_1 = 0;
		Moto_PWM_2 = 0;
		Moto_PWM_3 = 0;
		Moto_PWM_4 = 0;
	}
	if( RC_Control.THROTTLE < 1100 )//按键拨至解锁档位，油门低位，允许解锁
	{ 
		if( RC_Control.BUTTON > 1400 && RC_Control.BUTTON < 2100 )
		{
			lock= 0 ;
		}
	} 

	if( lock == 0 )//飞机解锁时动力分配才生效
	{
		Moto_PWM_1 = rc_in->THROTTLE + PID_ROL_Rate.OutPut - PID_PIT_Rate.OutPut - PID_YAW_Rate.OutPut;   
		Moto_PWM_2 = rc_in->THROTTLE - PID_ROL_Rate.OutPut - PID_PIT_Rate.OutPut + PID_YAW_Rate.OutPut;   
		Moto_PWM_3 = rc_in->THROTTLE - PID_ROL_Rate.OutPut + PID_PIT_Rate.OutPut - PID_YAW_Rate.OutPut;   
		Moto_PWM_4 = rc_in->THROTTLE + PID_ROL_Rate.OutPut + PID_PIT_Rate.OutPut + PID_YAW_Rate.OutPut;
		
	}
	
   Moto_Pwm(Moto_PWM_1,Moto_PWM_2,Moto_PWM_3,Moto_PWM_4); //将此数值分配到定时器，输出对应占空比的PWM波
}


