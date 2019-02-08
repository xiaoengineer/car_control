#include "motor.h"

static void TIM4_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//定时器4时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB时钟使能

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_TimeBaseStructure.TIM_Period = 7199;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数方式：向上计数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
}

static void ctrl_gpio(void)
{
	GPIO_InitTypeDef ctrl_gpio_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB时钟使能

	ctrl_gpio_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
	ctrl_gpio_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	ctrl_gpio_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &ctrl_gpio_InitStructure);
}

void motor_config(void)
{
	TIM4_GPIO_Config();
	TIM_Mode_Config();
	ctrl_gpio();
}

void motor(unsigned char cmd, unsigned int speed)
{
	if(0x12 == cmd) //左后 数字小速度大
	{
		TIM_SetCompare2(TIM4, speed);
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);
	}
	else if(0x21 == cmd) //左前 数字大速度大
	{
		TIM_SetCompare2(TIM4, speed);
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
	}
	else if(0x34 == cmd) //右后 数字小速度大
	{
		TIM_SetCompare3(TIM4, speed); 
		GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET); 
	}
	else if(0x43 == cmd) //有前 数字大速度大
	{
		TIM_SetCompare3(TIM4, speed);
		GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET);
	}
}


