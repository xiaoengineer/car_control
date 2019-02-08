#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void beep_gpio_config(void);
void delay(void);
void buzz_work(void);

#endif
