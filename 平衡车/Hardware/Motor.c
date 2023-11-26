#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Gpio.h"
void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = AIN1_GPIO_PIN;
	GPIO_Init(AIN1_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = AIN2_GPIO_PIN;
	GPIO_Init(AIN2_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = BIN1_GPIO_PIN;
	GPIO_Init(BIN1_GPIO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = BIN2_GPIO_PIN;
	GPIO_Init(BIN2_GPIO, &GPIO_InitStructure);
	
    GPIO_InitStructure.GPIO_Pin = STBY_GPIO_PIN;
	GPIO_Init(STBY_GPIO, &GPIO_InitStructure);
    
    STBY(1);
	PWM_Init();
}

void Motor_SetSpeed1(int8_t Speed)
{
	if (Speed >= 0)
	{
		AIN1(0);
        AIN2(1);
		PWM_SetCompare1(Speed);
	}
	else
	{
		AIN1(1);
        AIN2(0);
		PWM_SetCompare1(-Speed);
	}
}

void Motor_SetSpeed2(int8_t Speed)
{
	if (Speed >= 0)
	{
		BIN1(0);
        BIN2(1);
		PWM_SetCompare2(Speed);
	}
	else
	{
		BIN1(1);
        BIN2(0);
		PWM_SetCompare2(-Speed);
	}
}
