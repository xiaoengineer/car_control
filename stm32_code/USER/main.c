#include "stm32f10x.h"
#include "servor.h"
#include "motor.h"
#include "usart.h"
#include <stdio.h>
#include "beep.h"
#include "led.h"

//int test = 0;
//char sum = 10;
char left_flag = 0, right_flag = 0, buzz_flag = 0;
int Motor_A,Motor_B;

int main(void)
{

	sover_PWM();
	Motor_Gpio_init();
	PWM2_Init();
	buletooth_usart_config();
	beep_gpio_config();
	led_gpio_config();
	GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
	while(1)	
	{	

		if(left_flag)
		{
			left_led();
		}
		if(right_flag)
		{
			right_led();
		}
		if(!buzz_flag)
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
		}else
		{
			GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);
		}

	}
	
}

