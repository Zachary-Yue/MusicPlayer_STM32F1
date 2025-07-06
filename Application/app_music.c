
#include "app_music.h"

App_MusicState_t App_MusicState = APP_MUSIC_STOP;

void app_music_init(void)
{
    GPIO_InitTypeDef gpioInit =
    {
        .GPIO_Mode = GPIO_Mode_AF_PP,
        .GPIO_Pin = BUZ_PIN,
        .GPIO_Speed = GPIO_Speed_50MHz
    };
    GPIO_Init(BUZ_PORT, &gpioInit);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef timeBaseInit;
    timeBaseInit.TIM_ClockDivision = TIM_CKD_DIV1;
    timeBaseInit.TIM_CounterMode = TIM_CounterMode_Up;
    timeBaseInit.TIM_Prescaler = 1; // 分频后 18M
    timeBaseInit.TIM_Period = 0xffff;
    timeBaseInit.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(Music1_TIM, &timeBaseInit);

    TIM_OCInitTypeDef ocInit;
    TIM_OCStructInit(&ocInit);
    ocInit.TIM_OCMode = TIM_OCMode_Toggle;
    ocInit.TIM_OCPolarity = TIM_OCPolarity_High;
    ocInit.TIM_OutputState = TIM_OutputState_Enable;
    ocInit.TIM_Pulse = 0;
    TIM_OC1Init(Music1_TIM, &ocInit);

    TIM_ARRPreloadConfig(Music1_TIM, ENABLE);

    // 节省功耗
    TIM_ForceHigh();
    TIM_Cmd(Music1_TIM, ENABLE);
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
}
