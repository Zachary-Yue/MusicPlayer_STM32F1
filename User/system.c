
#include "system.h"


static void NVIC_Config(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    NVIC_InitTypeDef init;
    init.NVIC_IRQChannel = TIM1_UP_IRQn;
    init.NVIC_IRQChannelPreemptionPriority = 0;
    init.NVIC_IRQChannelSubPriority = 0;
    init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&init);
}

static void GPIO_RCC_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}


void System_Init(void)
{
    NVIC_Config();
    GPIO_RCC_Config();
}
