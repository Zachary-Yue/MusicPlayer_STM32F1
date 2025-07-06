
#include "task.h"
#include "music.h"
#include "freq_table.h"
#include "app_music.h"


#define CurrNote(_pm)       (_pm->melodies[MusicControl.pmelody].notes[MusicControl.pnote])
#define CurrMelody(_pm)     (_pm->melodies[MusicControl.pmelody])


/**
 * @brief 根据 MusicControl 中的指针，加载当前音符的时长和音调。
 * 
 * @param m 音乐结构体
 */
static void MusicNoteSet(const Music_t *m)
{
    MusicControl.curr_note_time = CurrNote(m).pulse * m->pulseToPeriodFactor;

    if (MusicControl.curr_note_time == 0)
    {
        // An Exceprion Occured.
        MusicStop();
        return;
    }

    if (CurrNote(m).pitch == PITCH_REST)
    {
        TIM_ForceHigh();
    }
    else
    {
        TIM_SetAutoreload(Music1_TIM, Get_Freq(CurrNote(m).pitch + m->transposition));
        TIM_OutputCompare();
    }
}


MusicControl_t MusicControl = { 0, 0, 0, Music_PAUSE };


/**
 * @brief 音乐播放任务。
 * @note  放在基准时间片的中断服务函数里。
 * 
 * @param m     音乐
 */
void MusicTask(const Music_t *m)
{
    if (MusicControl.state == Music_PAUSE) return;

    if (MusicControl.curr_note_time == 0)
    {
        // Next Note.
        if (++MusicControl.pnote >= CurrMelody(m).NumOfNotes)
        {
            MusicControl.pnote = 0;
            // Next Melody.
            if (++MusicControl.pmelody >= m->NumOfMelody)
            {
                MusicControl.pmelody = 0;
                // The Music Ends.
                MusicControl.state = Music_PAUSE;
                App_MusicState = APP_MUSIC_STOP;
                return;
            }
        }

        MusicNoteSet(m);
    }

    else if (MusicControl.curr_note_time-- == 1)
    {
        // REST
        TIM_ForceHigh();
    }
}


void MusicStart(const Music_t *m)
{
    MusicControl.pnote = 0;
    MusicControl.pmelody = 0;
    MusicNoteSet(m);
    MusicControl.state = Music_PLAY;
    TaskTimerPeriod_Modify(m->baiscTimePeriod);
}

void MusicResume(void)
{
    MusicControl.state = Music_PLAY;
    TIM_OutputCompare();
}

void MusicPause(void)
{
    MusicControl.state = Music_PAUSE;
    TIM_ForceHigh();
}

void MusicStop(void)
{
    MusicControl.pnote = 0;
    MusicControl.pmelody = 0;
    MusicControl.curr_note_time = 0;
    MusicControl.state = Music_PAUSE;
    TIM_ForceHigh();
    TaskTimerPeriod_Modify(30000 - 1);
}

void TIM_ForceHigh(void)
{
    MODIFY_REG(Music1_TIM->CCMR1, TIM_CCMR1_OC1M, TIM_OCMode_Active);
}

void TIM_OutputCompare(void)
{
    MODIFY_REG(Music1_TIM->CCMR1, TIM_CCMR1_OC1M, TIM_OCMode_Toggle);
}
