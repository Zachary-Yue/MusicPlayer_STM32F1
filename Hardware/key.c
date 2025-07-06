
#include "key.h"
#include "application.h"

#define LongPrs_THRES       ((u8)(600/20))
#define DblePrs_THRES       ((u8)(300/20))
#define DblePrs_DELAY       ((u8)(150/20))

static void LongPress(void)
{
    switch (App_MusicState)
    {
        default: break;

        case APP_MUSIC_PLAY:
        case APP_MUSIC_PAUSE:
        {
            App_MusicState = APP_MUSIC_STOP;
            MusicStop();
        } break;
    }
}

static void ShortPress(void)
{
    switch (App_MusicState)
    {
        case APP_MUSIC_STOP:
        {
            App_MusicState = APP_MUSIC_PLAY;
            MusicStart(&Music_HeadToFutureTogether);
        } break;

        case APP_MUSIC_PAUSE:
        {
            App_MusicState = APP_MUSIC_PLAY;
            MusicResume();
        } break;

        case APP_MUSIC_PLAY:
        {
            App_MusicState = APP_MUSIC_PAUSE;
            MusicPause();
        } break;

        default: break;
    }
}

static void DoublePress(void)
{
    ;
}

void KeyInit(void)
{
    GPIO_InitTypeDef init =
    {
        .GPIO_Mode = GPIO_Mode_IPU,
        .GPIO_Pin = KEY_PIN,
        .GPIO_Speed = GPIO_Speed_2MHz
    };
    GPIO_Init(KEY_PORT, &init);
}

void KeyTask(void)
{
    static u8 bl = Bit_SET;
    static u8 state = 0, count = 0;
    u8 bn = GPIO_ReadInputDataBit(KEY_PORT, KEY_PIN);

    switch (state)
    {
        case 0:
        {
            if (bl == Bit_SET && bn == Bit_RESET)
            {
                state = 1;
                count = 0;
            }
        } break;

        case 1:
        {
            if (bn == Bit_RESET)
            {
                if (++count > LongPrs_THRES)
                {
                    state = 0;
                    LongPress();
                }
            }
            else
            {
                state = 2;
                count = 0;
            }
        } break;

        case 2:
        {
            if (bn == Bit_SET)
            {
                if (++count > DblePrs_THRES)
                {
                    state = 0;
                    ShortPress();
                }
            }
            else
            {
                state = 3;
                count = DblePrs_DELAY;
            }
        } break;

        case 3:
        {
            if (--count == 0)
            {
                state = 0;
                DoublePress();
            }
        } break;

        default:
            state = 0;
            break;
    }

    bl = bn;
}
