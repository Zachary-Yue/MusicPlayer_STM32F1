
#include "led.h"
#include "app_music.h"


void led_init(void)
{
    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_Out_PP;
    init.GPIO_Pin = LED_PIN;
    init.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_PORT, &init);
}


static void led_toggle(void)
{
    if (GPIO_ReadOutputDataBit(LED_PORT, LED_PIN) == Bit_RESET)
    {
        GPIO_SetBits(LED_PORT, LED_PIN);
    }
    else
    {
        GPIO_ResetBits(LED_PORT, LED_PIN);
    }
}

#define led_on()    { GPIO_ResetBits(LED_PORT, LED_PIN); }
#define led_off()   { GPIO_SetBits(LED_PORT, LED_PIN); }

void led_task(void)
{
    switch (App_MusicState)
    {
        case APP_MUSIC_STOP: led_off() break;
        case APP_MUSIC_PAUSE: led_on() break;
        case APP_MUSIC_PLAY: led_toggle(); break;
    }
}
