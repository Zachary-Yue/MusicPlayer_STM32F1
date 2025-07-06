#ifndef __TASK_H
#define __TASK_H

#include "main.h"

extern u8 TaskExeFlag;

#define TaskTimerPeriod_Modify(x)       (TIM1->ARR = (x))

#define SET_TaskExeFlag()       (TaskExeFlag = 1)
#define CLR_TaskExeFlag()       (TaskExeFlag = 0)
#define GET_TaskExeFlag()       (TaskExeFlag)

void TaskInit(void);
void TaskExe(void);

#endif // !__TASK_H
