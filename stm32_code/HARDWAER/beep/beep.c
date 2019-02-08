#include "beep.h"

void beep_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void delay(void)
{
	int i = 10000;
	while(i --);
}

void buzz_work(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
	delay();
	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
}
