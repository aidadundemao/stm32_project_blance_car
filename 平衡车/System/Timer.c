#include "stm32f10x.h"                  // Device header

//1、跨文件使用变量
//extern uint16_t num;


void Timer_Init(void)
{
	//1、开启rcc时钟，TIM1是在APB2总线上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//2、选择时基单元的时钟源（默认内部时钟）
	TIM_InternalClockConfig(TIM1);
	
	//3、配置时钟单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //一分频
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	//时基单元里面每个关键寄存器的参数
	//取值范围0到65535之间
	//f定时频率=72000000hz/(PSC+1)/(ARR+1)
	//定时0.5秒
	
	TIM_TimeBaseInitStruct.TIM_Prescaler =7200 - 1 ;
	//在10k的频率下，记5000个数
	TIM_TimeBaseInitStruct.TIM_Period =5000 - 1;
	//重复记数器
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

	TIM_ClearFlag(TIM1,TIM_IT_Update);
	
	//4、使能更新中断
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	//5、配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel= TIM1_UP_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//启动定时器
	TIM_Cmd(TIM1,ENABLE);

}

//中断函数是服务函数，中断函数可以放到使用的地方
/**
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_CounterMode_Up) == SET)
	{
	    num++;
	
		TIM_ClearITPendingBit(TIM2,TIM_CounterMode_Up);
	}
	
}
*/
