/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*						张润
*						杨晨阳
************************************************************************************************/

#include "pid.h"

/*****************************************************************************
* 函  数：void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
* 功  能：位置式PID算法
* 参  数：PID: 算法P I D参数的结构体
*         target: 目标值
*         measure: 测量值 
* 返回值：无 
* 备  注: 角度环和角速度环共用此函数
*****************************************************************************/
void PID_Postion_Cal(PID_TYPE*PID,float target,float measure)
{
	PID->Error  = target - measure;           					    //误差
	PID->Differ = PID->Error - PID->PreError;   						//微分量
	
	PID->Pout = PID->P * PID->Error;                        //比例控制
	PID->Iout = PID->Ilimit_flag * PID->I * PID->Integral;  //积分控制
	PID->Dout = PID->D * PID->Differ;                       //微分控制
	
	PID->OutPut =  PID->Pout + PID->Iout + PID->Dout;       //比例 + 积分 + 微分总控制
	//RC_Control.THROTTLE变化范围是 1000-2000
	if( RC_Control.BUTTON > 1400 && RC_Control.BUTTON < 2100 && RC_Control.THROTTLE >= 180 )  //飞机解锁之后再加入积分,防止积分过调
	{
		if(measure > (PID->Ilimit)||measure < -PID->Ilimit)   //积分分离（当被控量和设定值偏差较大时，取消积分作用）
		{PID->Ilimit_flag = 0;}
		else
		{
			PID->Ilimit_flag = 1;                               //加入积分（积分分离标志为1，即积分项参与调节）
			PID->Integral += PID->Error;                        //对误差进行积分
			if(PID->Integral > PID->Irang)                      //积分限幅
				PID->Integral = PID->Irang;
			if(PID->Integral < -PID->Irang)                     //积分限幅
			    PID->Integral = -PID->Irang;                    
		}
	}else
	{
	PID->Integral = 0;
	}
	PID->PreError = PID->Error ;                            //前一个误差值
}

/*****************************************************************************
* 函  数：void PidParameter_init(void)
* 功  能：初始化PID结构体里的一些成员值
* 参  数：无
* 返回值：无 
* 备  注: 不使用flash存储PID参数 运行时所有参数全部进行初始化
*****************************************************************************/
void PidParameter_init(void)
{
	//ROLL轴
	PID_ROL_Angle.P = 6;			//4.5				6.5 较好		2022/8/19 23:00 可以飞行较长一段时间
	PID_ROL_Angle.I = 0;			//0   0.000719		0.000219
	PID_ROL_Angle.D = 0;				//  10 大
	
	PID_ROL_Rate.P = 0.9;
  PID_ROL_Rate.I = 0.0085;
	PID_ROL_Rate.D = 1.2;
	
	PID_ROL_Rate.Ilimit_flag = 0; //Roll轴角速度积分的分离标志
	PID_ROL_Rate.Ilimit = 300;    //Roll轴角速度积分范围
	PID_ROL_Rate.Irang = 400;    //Roll轴角速度积分限幅度（由于电机输出有限，所以积分输出也是有限的）
	
	PID_ROL_Angle.Ilimit_flag = 0;//Roll轴角度积分的分离标志
	PID_ROL_Angle.Ilimit = 35;    //Roll轴角度积分范围			35
	PID_ROL_Angle.Irang = 200;    //Roll轴角度积分限幅度（由于电机输出有限，所以积分输出也是有限的）		200

	//PITCH轴
	PID_PIT_Angle.P = 6;
	PID_PIT_Angle.I = 0;
	PID_PIT_Angle.D = 0;
	
  PID_PIT_Rate.P = 0.9;
	PID_PIT_Rate.I =0.0085;
	PID_PIT_Rate.D = 1.2;
	
	PID_PIT_Rate.Ilimit_flag = 0; //Pitch轴角速度积分的分离标志
	PID_PIT_Rate.Ilimit = 300;    //Pitch轴角速度积分范围
	PID_PIT_Rate.Irang = 400;    //Pitch轴角速度积分限幅度（由于电机输出有限，所以积分输出也是有限的）
	
	PID_PIT_Angle.Ilimit_flag = 0;//Roll轴角度积分的分离标志
	PID_PIT_Angle.Ilimit = 35;    //Roll轴角度积分范围
	PID_PIT_Angle.Irang = 1000;    //Roll轴角度积分限幅度（由于电机输出有限，所以积分输出也是有限的）
	
	//YAW轴
	PID_YAW_Angle.P = 6;
	PID_YAW_Angle.I = 0; 
	PID_YAW_Angle.D = 0;
	
	PID_YAW_Rate.P = 1.5;
	PID_YAW_Rate.I = 0;
	PID_YAW_Rate.D = 0;
	
	PID_YAW_Rate.Ilimit_flag = 0; //Yaw轴角速度积分的分离标志
	PID_YAW_Rate.Ilimit = 150;    //Yaw轴角速度积分范围
	PID_YAW_Rate.Irang = 1200;    //Yaw轴角速度积分限幅度（由于电机输出有限，所以积分输出也是有限的）
	
	PID_YAW_Angle.Ilimit_flag = 0;//Yaw轴角度积分的分离标志
	PID_YAW_Angle.Ilimit = 35;    //Yaw轴角度积分范围
	PID_YAW_Angle.Irang = 200;    //Yaw轴角度积分限幅度（由于电机输出有限，所以积分输出也是有限的）

}

