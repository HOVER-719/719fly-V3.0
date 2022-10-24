/************************************************************************************************
* 程序版本：V2.1
* 程序日期：2021-12-8
* 程序作者：719飞行器实验室： 
*                        张润
*                        杨晨阳
************************************************************************************************/

#include "led.h"
uint8_t loop=0;
/************************************************************************************************
* 函  数：void LED_Init(void)
* 功  能：用户指示灯引脚初始化
* 参  数：无
* 返回值：无
* 备  注: 无
************************************************************************************************/
void LED_Init(void)
{
    
    GPIO_InitTypeDef GPIO_InitStruct;   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  
    
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14; 
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;                                            //推挽输出
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB,&GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;                                            //推挽输出
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);
    
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    GPIO_ResetBits(GPIOB,GPIO_Pin_14);
    
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}


void LEDR_1(void)
{
        LEDR_L ;
        Delay_ms (100);
        LEDR_H ;
        Delay_ms (100);
}

void LEDR_2(void)
{
        LEDR_L ;
        Delay_ms (100);
        LEDR_H ;
        Delay_ms (100);
        LEDR_L ;
        Delay_ms (100);
        LEDR_H ;
        Delay_ms (100);
}

void LEDR_3(void)
{
        LEDR_L ;
        Delay_ms (100);
        LEDR_H ;
        Delay_ms (100);
        LEDR_L ;
        Delay_ms (100);
        LEDR_H ;
        Delay_ms (100);
        LEDR_L ;
        Delay_ms (100);
        LEDR_H ;
        Delay_ms (100);
}


void LEDG_1(void)
{
        LEDG_L ;
        Delay_ms (100);
        LEDG_H ;
        Delay_ms (100);
}

void LEDG_2(void)
{
        LEDG_L ;
        Delay_ms (100);
        LEDG_H ;
        Delay_ms (100);
        LEDG_L ;
        Delay_ms (100);
        LEDG_H ;
        Delay_ms (100);
}

void LEDG_3(void)
{
        LEDG_L ;
        Delay_ms (100);
        LEDG_H ;
        Delay_ms (100);
        LEDG_L ;
        Delay_ms (100);
        LEDG_H ;
        Delay_ms (100);
        LEDG_L ;
        Delay_ms (100);
        LEDG_H ;
        Delay_ms (100);
}

void LEDB_1(void)
{
        LEDB_L ;
        Delay_ms (100);
        LEDB_H ;
        Delay_ms (100);
}

void LEDB_2(void)
{
        LEDB_L ;
        Delay_ms (100);
        LEDB_H ;
        Delay_ms (100);
        LEDB_L ;
        Delay_ms (100);
        LEDB_H ;
        Delay_ms (100);
}

void LEDB_3(void)
{
        LEDB_L ;
        Delay_ms (100);
        LEDB_H ;
        Delay_ms (100);
        LEDB_L ;
        Delay_ms (100);
        LEDB_H ;
        Delay_ms (100);
        LEDB_L ;
        Delay_ms (100);
        LEDB_H ;
        Delay_ms (100);
}


