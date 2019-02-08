#include "led.h"

void led_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void led_delay(void)
{
	int i = 100000;
	while(i --);
}

void left_led(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_RESET);
	led_delay();
	GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_SET);
}

void right_led(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
	led_delay();
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
}

void big_led(char cmd)
{
	if(cmd == 1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
	}
	else
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
	}

}

void litte_led(char cmd)
{
	if(cmd == 1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
	}
	else
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
	}
	
}

