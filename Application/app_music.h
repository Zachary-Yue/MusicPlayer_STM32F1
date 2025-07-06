
#pragma once

#include "music.h"
#include "main.h"

#define BUZ_PORT        GPIOA
#define BUZ_PIN         GPIO_Pin_0

typedef enum _app_music_state
{
    APP_MUSIC_STOP,
    APP_MUSIC_PLAY,
    APP_MUSIC_PAUSE,
} App_MusicState_t;

extern App_MusicState_t App_MusicState;

void app_music_init(void);
