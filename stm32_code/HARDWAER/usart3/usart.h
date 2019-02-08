#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include <stdio.h>

void buletooth_usart_config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
#endif
