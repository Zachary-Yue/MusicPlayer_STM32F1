
#include "task.h"
#include "hardware.h"
#include "application.h"

u8 TaskExeFlag = 0;

typedef struct __task
{
    const u16 period;
    u16 count;
    void (*task_hook)(void);
} task_t;

#define TASK_TOTAL      2

task_t task[TASK_TOTAL] =
{
    { 200/5, 0, led_task },
    { 20/5, 0, KeyTask },
};

void TaskExe(void)
{
    u8 i = 0;
    for (; i < TASK_TOTAL; i++)
    {
        if (++task[i].count >= task[i].period)
        {
            task[i].count = 0;
            if (task[i].task_hook)
            {
                task[i].task_hook();
            }
        }
    }
}

void TaskInit(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    
    TIM_TimeBaseInitTypeDef init;
    init.TIM_ClockDivision = TIM_CKD_DIV1;
    init.TIM_CounterMode = TIM_CounterMode_Up;
    init.TIM_Prescaler = 12 - 1;
    init.TIM_Period = 30000 - 1;
    init.TIM_RepetitionCounter = 0;
    // 设置定时器 1 每 5 ms 溢出一次
    TIM_TimeBaseInit(TIM1, &init);

    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM1, ENABLE);
}

void TIM1_UP_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    SET_TaskExeFlag();
    MusicTask(&Music_HeadToFutureTogether);
}
