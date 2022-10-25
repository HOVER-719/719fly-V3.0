#include "main.h"
#include "system.h"
#include "led.h"
#include <stdbool.h>

extern uint8_t Init_Flag;

void System_Init(void)
{
    LED_Init();                                        //״ָ̬ʾ�Ƴ�ʼ��
    // NvicConfig();                                 //ϵͳ�ж����ȼ������������жϳ�ʼ����
    // Delay_Init();                                 //ϵͳ��ʱ��ʼ��
    USART_init(115200);                        //���Դ��ڳ�ʼ��
    IIC_GPIO_Init();                             //ģ��IIC��ʼ��
    TIM_Init();                                        //ϵͳʱ����ʼ����TIM4��Ϊϵͳʱ��
    //MPU6050_Init();                                 //MPU6050��ʼ��
    MOTOR_Init();                                 //��������ʼ��
    PidParameter_init();                     //PID������ʼ��
    GENERAL_TIM_Init();                        //TIM2��TIM1��ʼ�������жϳ�ʼ�� ���ڶԽ��ջ��źŽ������벶��

    Butterworth_Parameter_Init();
    xInit_Kalman(); //newAngle �Ƕ�
    yInit_Kalman();
    zInit_Kalman();
}



static const task_list_t high_frequent_task_list[] =
{
    {"led", led_task, 1024, 4},
};

// static const task_list_t mid_frequent_task_list[] =
// {
//     {"led", led_task, 1024, 4},
// };

// static const task_list_t low_frequent_task_list[] =
// {
//     {"led", led_task, 1024, 4},
// };

//xTaskCreate(Task_Schedule, "high_frequent_task", 1024, NULL, configMAX_PRIORITIES-1, NULL);//任务调度
static uint8_t task_creat_list(const task_list_t task_list[])
{
    uint32_t list_num = sizeof(*task_list)/sizeof(task_list_t);
    task_list_t *cur_task = NULL;
    int32_t ret;

    for(uint32_t num = 0; num < list_num; num++)
    {
        cur_task = (task_list_t *)&task_list[num];
        ret = xTaskCreate((TaskFunction_t)cur_task->task_func, cur_task->name, cur_task->stack_size, NULL, cur_task->priority, NULL);
        printf("create task %s %s\r\n", cur_task->name, ret == true ? "success" : "false");
    }
    return 0;
}

TaskFunction_t Task_Schedule()
{
    task_creat_list(high_frequent_task_list);
    //task_creat_list(mid_frequent_task_list);
    //task_creat_list(low_frequent_task_list);

    vTaskDelete(NULL);

    return 0;
    // if(IMU_Scan)                                                                                                                 //100Hz
    // {
    //     IMU_Scan  = 0;                                                                                                    //��־λ����
    //     Prepare_Data();                                                                                                 //��ȡ��̬������������
    //     IMUupdate(&Gyr_rad,&Acc_filt,&Att_Angle);                                             //��Ԫ����̬����
    //     Control(&Att_Angle,&Gyr_rad,&RC_Control,Airplane_Enable);             //��̬����
    // }
    // if(LED_Scan) //10Hz
    // {
    //     LED_Scan = 0;
    //     if( Init_Flag == 0 )//��ʼ��������R����˸
    //     {
    //         LEDR_H;
    //         LEDG_H;
    //         LEDB_H;
    //         if(loop)
    //         {
    //             loop=0;
    //             LEDR_H;
    //         }
    //         else
    //         {
    //             loop=1;
    //             LEDR_L;
    //         }
    //     }
    //     if( lock && Init_Flag == 1 )//��ʼ����ɣ��ɻ�������ң�����ź�����,G����˸
    //     {
    //         LEDR_H;
    //         LEDG_H;
    //         LEDB_H;
    //         if(loop)
    //         {
    //             loop=0;
    //             LEDG_H;
    //         }
    //         else
    //         {
    //             loop=1;
    //             LEDG_L;
    //         }
    //     }
    //     if( !lock && Init_Flag == 1)//��ʼ����ɣ��ɻ�����,B����˸
    //     {
    //         LEDR_H;
    //         LEDG_H;
    //         LEDB_H;
    //         if(loop)
    //         {
    //             loop=0;

    //             LEDB_H;
    //         }
    //         else
    //         {
    //             loop=1;

    //             LEDB_L;
    //         }

    //     }
    // }
}


