
#pragma once

#include "main.h"

#define KEY_PORT        GPIOA
#define KEY_PIN         GPIO_Pin_2

void KeyInit(void);
void KeyTask(void);
