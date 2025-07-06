
#include "app_music.h"

App_MusicState_t App_MusicState = APP_MUSIC_STOP;

/**
 * @brief 负责播放音乐的定时器初始化。
 * 
 */
void app_music_init(void)
{
    // 配置 TIM2 CH1
    GPIO_InitTypeDef gpioInit =
    {
        .GPIO_Mode = GPIO_Mode_AF_PP,
        .GPIO_Pin = BUZ_PIN,
        .GPIO_Speed = GPIO_Speed_50MHz
    };
    GPIO_Init(BUZ_PORT, &gpioInit);

    // 配置 TIM2
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

    // 使能 ARR 预装载寄存器，方便随时更改重装值而不出现错误时序
    TIM_ARRPreloadConfig(Music1_TIM, ENABLE);

    // 没有播放的时候强制输出高电平（因为我的无源蜂鸣器是低电平触发，一直低电平会发热）
    TIM_ForceHigh();
    // 使能 TIM2，永不关闭（如果关了那就没法强制输出高电平了，比较麻烦）
    TIM_Cmd(Music1_TIM, ENABLE);
}
