#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

void motor_config(void);
void motor(unsigned char cmd, unsigned int speed);

#endif
