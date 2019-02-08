#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

#define PWMA1   TIM4->CCR1  
#define PWMA2   TIM4->CCR2 

#define PWMB1   TIM4->CCR3  
#define PWMB2   TIM4->CCR4

void Motor_Gpio_init(void);
void PWM2_Init(void);
void Set_Pwm_Motor1(int motor_a);
void Set_Pwm_Motor2(int motor_b);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
void Xianfu_Pwm(void);

#endif
