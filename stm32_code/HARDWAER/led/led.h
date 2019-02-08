#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void led_gpio_config(void);
void led_delay(void);
void left_led(void);
void right_led(void);
void big_led(char cmd);
void litte_led(char cmd);

#endif
