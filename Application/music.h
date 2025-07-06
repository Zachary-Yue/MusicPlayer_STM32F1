
#pragma once

#include "stm32f10x.h"

#define Music1_TIM           TIM2

// 音符，不可相加
typedef enum __Pitch
{
    PITCH_C4, PITCH_bD4, PITCH_D4, PITCH_bE4, PITCH_E4, PITCH_F4, PITCH_bG4, PITCH_G4, PITCH_bA4, PITCH_A4, PITCH_bB4, PITCH_B4,
    PITCH_C5, PITCH_bD5, PITCH_D5, PITCH_bE5, PITCH_E5, PITCH_F5, PITCH_bG5, PITCH_G5, PITCH_bA5, PITCH_A5, PITCH_bB5, PITCH_B5,
    PITCH_C6, PITCH_bD6, PITCH_D6, PITCH_bE6, PITCH_E6, PITCH_F6, PITCH_bG6, PITCH_G6, PITCH_bA6, PITCH_A6, PITCH_bB6, PITCH_B6,
    PITCH_C7, PITCH_bD7, PITCH_D7, PITCH_bE7, PITCH_E7, PITCH_F7, PITCH_bG7, PITCH_G7, PITCH_bA7, PITCH_A7, PITCH_bB7, PITCH_B7,
    PITCH_REST,
} Pitch_t;


// 音符时长记号，可以相加，转换到周期重装值需要 *10
typedef enum __Pulse
{
    PULSE_1_8   = (u8)1,
    PULSE_1_4   = (u8)2,
    PULSE_1_2   = (u8)4,
    PULSE_1     = (u8)8,
    PULSE_2     = (u8)16,
    PULSE_4     = (u8)32,
    PULSE_8     = (u8)64,
} Pulse_t;


typedef struct __Note
{
    u8 pitch;
    u8 pulse;
} Note_t;

typedef struct __Melody
{
    Note_t *notes;
    u16 NumOfNotes;
} Melody_t;

typedef struct __Music
{
    Melody_t *melodies;
    u8 NumOfMelody;
    s8 transposition;   // 一首歌的移调，取值 -128 ~ 127
    u8 pulseToPeriodFactor;     // Note 的 pulse 值转换到 curr_note_time 的因子
    u16 baiscTimePeriod;        // 标准时间片时间 (在 5 ms 上下浮动，为了适应音乐速度而微调)
} Music_t;


#define Music_PAUSE     0
#define Music_PLAY      1

typedef struct __MusicControl
{
    u8  pmelody;
    u16 pnote;

    u16 curr_note_time;

    u8  state;
} MusicControl_t;

extern MusicControl_t MusicControl;


void MusicTask(const Music_t *m);

void MusicStart(const Music_t *m);
void MusicResume(void);
void MusicPause(void);
void MusicStop(void);

void TIM_ForceHigh(void);
void TIM_OutputCompare(void);
