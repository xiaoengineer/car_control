#include "motor.h"

static void TIM4_GPIO_Config(unsigned char cmd)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//定时器4时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB时钟使能
	switch(cmd)
	{
		case 0x10:
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
			break;
		case 0x20:
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
			break;			
		case 0x30:
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
			break;
		case 0x40:
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
			break;	
		default: break;
	}
}

static void TIM_Mode_Config(unsigned char cmd)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	TIM_TimeBaseStructure.TIM_Period = 1100;
	TIM_TimeBaseStructure.TIM_Prescaler = 30;
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
	
	switch(cmd)
	{
		case 0x10:
			TIM_OC1Init(TIM4, &TIM_OCInitStructure);
			TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
			break;
		case 0x20:
			TIM_OC2Init(TIM4, &TIM_OCInitStructure);
			TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			break;
		case 0x30:
			TIM_OC3Init(TIM4, &TIM_OCInitStructure);
			TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
			break;	
		case 0x40:
			TIM_OC4Init(TIM4, &TIM_OCInitStructure);
			TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
			break;		
		default: break;	
	}
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
}

static void ctrl_gpio(unsigned char cmd)
{
	GPIO_InitTypeDef ctrl_gpio_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB时钟使能
	switch(cmd)
	{
		case 0x01:
			ctrl_gpio_InitStructure.GPIO_Pin = GPIO_Pin_6;
			ctrl_gpio_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			ctrl_gpio_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &ctrl_gpio_InitStructure);
			break;
		case 0x02:
			ctrl_gpio_InitStructure.GPIO_Pin = GPIO_Pin_7;
			ctrl_gpio_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			ctrl_gpio_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &ctrl_gpio_InitStructure);
			break;
		case 0x03:
			ctrl_gpio_InitStructure.GPIO_Pin = GPIO_Pin_8;
			ctrl_gpio_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			ctrl_gpio_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &ctrl_gpio_InitStructure);
			break;
		case 0x04:
			ctrl_gpio_InitStructure.GPIO_Pin = GPIO_Pin_9;
			ctrl_gpio_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			ctrl_gpio_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &ctrl_gpio_InitStructure);
			break;
		default:break;
	}
}

void motor(unsigned char cmd, unsigned int speed)
{
	if(0x12 == cmd) //左后 数字小速度大
	{
		TIM4_GPIO_Config(0x10);
		TIM_Mode_Config(0x10);
		ctrl_gpio(0x02);
		TIM_SetCompare1(TIM4, speed);
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
	}
	else if(0x21 == cmd) //左前 数字大速度大
	{
		TIM4_GPIO_Config(0x20);
		TIM_Mode_Config(0x20);
		ctrl_gpio(0x01);
		TIM_SetCompare2(TIM4, speed);
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
	}
	else if(0x34 == cmd) //右后 数字小速度大
	{
		TIM4_GPIO_Config(0x30);
		TIM_Mode_Config(0x30);
		ctrl_gpio(0x04);
		TIM_SetCompare3(TIM4, speed); 
		GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET); 
	}
	else if(0x43 == cmd) //有前 数字大速度大
	{
		TIM4_GPIO_Config(0x40);
		TIM_Mode_Config(0x40);
		ctrl_gpio(0x03);
		TIM_SetCompare4(TIM4, speed);
		GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
	}
}


