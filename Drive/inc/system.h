#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"

typedef __packed struct
{
    const char *name;
    TaskFunction_t (*task_func)();
    uint16_t   stack_size;
    uint8_t    priority;
} task_list_t;

TaskFunction_t Task_Schedule(void);

#endif
