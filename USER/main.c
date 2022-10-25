/************************************************************************************************
* 程序版本：V2.3
* 程序日期：2022-8-27
* 程序作者：719飞行器实验室：
*                        张润
*                        杨晨阳
*                        张天鹏
*                        竹显磊
*                        赵艺超

V2.2更新说明：
增加了OLED屏幕显示功能

V2.3更新说明：
优化MPU6050校准零偏功能
增加油门安全保护功能，当油门不在低位时拒绝解锁
************************************************************************************************/

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdint.h"

/************************************************************************************************
* 函  数：int main(void)
* 功  能：主函数
* 参  数：
* 返回值：无
* 备  注：本程序为STM32飞控新生比赛精简版
************************************************************************************************/

#define ITM_PORT8(n)         (*(volatile unsigned char *)(0xe0000000 + 4*(n)))
#define ITM_PORT16(n)        (*(volatile unsigned short *)(0xe0000000 + 4*(n)))
#define ITM_PORT32(n)        (*(volatile unsigned long *)(0xe0000000 + 4*(n)))
#define DEMCR                (*(volatile unsigned long *)(0xE000EDFC))
#define TRCENA               0X01000000

int fputc(int ch, FILE *f)
{
    if(DEMCR & TRCENA)
    {
        while(ITM_PORT32(0) == 0);
        ITM_PORT8(0) = ch;
    }
    return ch;
}

TaskFunction_t led_test()
{
    static uint32_t clock = 0;
    while (1)
    {
        if(clock % 2 == 0)
        {
            LEDR_H;
            LEDG_H;
            LEDB_H;
        }
        else
        {
            LEDR_L;
            LEDG_L;
            LEDB_L;
        }
        clock++;
        printf("start main sdf \n\r");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    return 0;
}

void main(void)
{
    System_Init();//系统初始化

    xTaskCreate(Task_Schedule, "task", 1024, NULL, configMAX_PRIORITIES-1, NULL);//任务调度
    vTaskStartScheduler();

    while(1);
    // {
    //     Task_Schedule();
    // }
}
