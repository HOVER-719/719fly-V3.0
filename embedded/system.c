#include "main.h"
#include "system.h"
#include "led.h"
#include <stdbool.h>

void System_Init(void)
{
    LED_Init();
    NvicConfig();
    // Delay_Init();
    USART_init(115200);
    IIC_GPIO_Init();
    //TIM_Init();
    MPU6050_Init();
    MOTOR_Init();
    PidParameter_init();
    GENERAL_TIM_Init();

    Butterworth_Parameter_Init();
    xInit_Kalman();
    yInit_Kalman();
    zInit_Kalman();
}

void ctrl()
{
    while (1)
    {
        TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
        Prepare_Data();
        IMUupdate(&Gyr_rad,&Acc_filt,&Att_Angle);
        Control(&Att_Angle,&Gyr_rad,&RC_Control,Airplane_Enable);
    }
}

static const task_list_t high_frequent_task_list[] =
{
    {"ctrl", ctrl, 1024, 4},
};

static const task_list_t mid_frequent_task_list[] =
{
    {0},
};

static const task_list_t low_frequent_task_list[] =
{
    {"led",       led_task, 1024, 4},
    //{"led_heart", led_test, 1024, 4},
};

static uint8_t task_creat_list(const task_list_t task_list[])
{
    uint32_t list_num = sizeof(*task_list)/sizeof(task_list_t);
    task_list_t *cur_task = NULL;
    int32_t ret;

    for(uint32_t num = 0; num < list_num; num++)
    {
        cur_task = (task_list_t *)&task_list[num];
        ret = xTaskCreate(cur_task->task_func, cur_task->name, cur_task->stack_size, NULL, cur_task->priority, NULL);
        printf("create task %s %s\r\n", cur_task->name, ret == true ? "success" : "false");
    }
    return 0;
}

void Task_Schedule(void* pvParameters)
{
    task_creat_list(high_frequent_task_list);
    task_creat_list(mid_frequent_task_list);
    task_creat_list(low_frequent_task_list);

    vTaskDelete(NULL);
}
