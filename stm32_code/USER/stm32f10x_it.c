/**
  ******************************************************************************
  ******************************************************************************
  * @file 1rst_CEC_Device/src/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V2.0.0
  * @date  04/27/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"



/** @addtogroup 1rst_CEC_Device
  * @{
  */ 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MyDeviceAddress  0x01 /* My device address: is my initiator address
                                 in case of transmit and the follower address
                                 in case of receive */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Receive buffer */
uint8_t ReceiveBuffer[10]; 
/* Transmit buffer 1 */
uint8_t TransmitBuffer1[10]={0xdf,0x12,0xd3,0x56,0x97,0xa1,0xec,0x7b,0x4f,0x22};
/* Transmit buffer 2 */
uint8_t TransmitBuffer2[5]={0xdc,0xaf,0x43,0x97,0xbe};

extern uint8_t ReceivedFrame;
extern uint8_t SendFrame;
extern uint32_t ReceiveInfos;
uint8_t i=0;
ErrorStatus SendStatus = ERROR;
extern uint8_t *BufferPointer;
extern uint8_t ByteNumber;
extern uint8_t SendTo;

int sum = 170;
unsigned int speed = 2000;
char led_flag = 1, direction_flag;
extern char left_flag, right_flag, buzz_flag;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
   
}


/**
  * @brief  This function handles EXTI0 interrupt request.
  * @param  None
  * @retval : None
  */
void EXTI0_IRQHandler(void)
{

}

/**
  * @brief  This function handles EXTI9_5 interrupt request.
  * @param  None
  * @retval : None
  */
void EXTI9_5_IRQHandler(void)
{
  
  
}

// 串口中断服务函数
void USART3_IRQHandler(void) 
{
  char ucTemp;
  //unsigned char cmd, tmp, angle, distance;
  
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(USART3);
		printf("run...");

		if(ucTemp == 0x01)
		{
			
			if(sum > 200)
			{
				sum = 200;
			}
			sover_ctrl(sum);
			sum = sum + 15;
			GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
		}
		if(ucTemp == 0x00)
		{
			
			if(sum < 70)
			{
				sum = 75;
			}
			sover_ctrl(sum);
			sum = sum - 15;
			GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
		}
		if(ucTemp == 0x02  && (direction_flag == 1)) //前进速度加
		{
			if(speed >6500)
			{
				speed = 6500;
			}
			Set_Pwm_Motor1(speed);
			Set_Pwm_Motor2(0-speed);
			if(speed < 2000)
			{
				speed = 2000;
			}
			else
			{
				speed = speed + 500;
			}
		}
		if((ucTemp == 0x03)  && (direction_flag == 1)) //前进速度减
		{
			if(speed >6500)
			{
				speed = 6500;
			}
			Set_Pwm_Motor1(speed);
			Set_Pwm_Motor2(0-speed);
			if(speed < 200)
			{
				speed = 2000;
			}
			else
			{
				speed = speed - 500;
			}
		}
		if(ucTemp == 0x02  && (direction_flag == 2)) //后退速度加
		{
			if(speed >6500)
			{
				speed = 6500;
			}
			Set_Pwm_Motor1(0-speed);
			Set_Pwm_Motor2(speed);
			if(speed < 2000)
			{
				speed = 2000;
			}
			else
			{
				speed = speed + 500;
			}
		}
		if((ucTemp == 0x03)  && (direction_flag == 2)) //后退速度减
		{
			if(speed >6500)
			{
				speed = 6500;
			}
			Set_Pwm_Motor1(0-speed);
			Set_Pwm_Motor2(speed);
			if(speed < 2000)
			{
				speed = 2000;
			}
			else
			{
				speed = speed - 500;
			}
		}
		if(ucTemp == 0x04) //停止
		{
			Set_Pwm_Motor1(0);
			Set_Pwm_Motor2(0);
			speed = 0;
			direction_flag = 0;
			
		}
		if(ucTemp == 0x05) //蜂鸣器
		{
			buzz_flag = ~buzz_flag;
		}
		if(ucTemp == 0x06) //灯
		{

			if(led_flag > 4)
			{
				led_flag = 1;
			}
			if(led_flag == 1)
			{
				big_led(2);
			}
			if(led_flag == 2)
			{
				litte_led(1);
			}
			if(led_flag == 3)
			{
				big_led(1);
			}
			led_flag ++;
		}
		if(ucTemp == 0x07)
		{
			left_flag = ~left_flag;
		}
		if(ucTemp == 0x08)
		{
			right_flag = ~right_flag;
		}
		if(ucTemp == 0x09)
		{
			direction_flag = 1;
		}
		if(ucTemp == 0x0a)
		{
			direction_flag = 2;
		}

	}	 
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (1rst_CEC_Device_src), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles 1rst_CEC_Device_src interrupt request.
  * @param  None
  * @retval : None
  */
/*void 1rst_CEC_Device_src_IRQHandler(void)
{
}*/

/**
  * @}
  */ 




/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
