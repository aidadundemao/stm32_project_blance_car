#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

extern uint8_t receiveData[255];
extern uint8_t receiveFinish;
void GPIO_USART1_Init(uint32_t BaudRate);	
	
#endif
