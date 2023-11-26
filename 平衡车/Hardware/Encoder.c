#include "stm32f10x.h"                  // Device header

uint16_t num;


void Encoder_Init(void)
{
	//1、开启TIM3的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//初始化输入的GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IPU;//上拉输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//3、配置时钟单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_Period= 65536-1;	   //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler= 1-1;  //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter= 0x00;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
    
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0x01;
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0x01;
	//TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
    
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	//启动定时器
	TIM_Cmd(TIM3,ENABLE);

}


void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_CounterMode_Up) == SET)
	{
	    num = TIM_GetCounter(TIM3);
        TIM_SetCounter(TIM3,0);
		TIM_ClearITPendingBit(TIM1,TIM_CounterMode_Up);
	}
	
}
