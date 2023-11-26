#include "stm32f10x.h"                  // Device header

//1�����ļ�ʹ�ñ���
//extern uint16_t num;


void Timer_Init(void)
{
	//1������rccʱ�ӣ�TIM1����APB2������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//2��ѡ��ʱ����Ԫ��ʱ��Դ��Ĭ���ڲ�ʱ�ӣ�
	TIM_InternalClockConfig(TIM1);
	
	//3������ʱ�ӵ�Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; //һ��Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
	//ʱ����Ԫ����ÿ���ؼ��Ĵ����Ĳ���
	//ȡֵ��Χ0��65535֮��
	//f��ʱƵ��=72000000hz/(PSC+1)/(ARR+1)
	//��ʱ0.5��
	
	TIM_TimeBaseInitStruct.TIM_Prescaler =7200 - 1 ;
	//��10k��Ƶ���£���5000����
	TIM_TimeBaseInitStruct.TIM_Period =5000 - 1;
	//�ظ�������
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

	TIM_ClearFlag(TIM1,TIM_IT_Update);
	
	//4��ʹ�ܸ����ж�
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	//5������NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel= TIM1_UP_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//������ʱ��
	TIM_Cmd(TIM1,ENABLE);

}

//�жϺ����Ƿ��������жϺ������Էŵ�ʹ�õĵط�
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
