#ifndef __LED_H
#define __LED_H

#include "main.h"

#define LED_PORT        GPIOC
#define LED_PIN         GPIO_Pin_13

void led_init(void);
void led_task(void);

#endif // !__LED_H
