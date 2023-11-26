
#include "led.h"
/*******************************************************************************
 ��������: GPIO_LED_Init
 ����˵��: GPIO�ڳ�ʼ������ 
 �������: ��  
 �� �� ֵ: ��  
*******************************************************************************/
void GPIO_LED_Init(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;	                     //����һ���ṹ�����GPIO_InitStructure
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);//ʹ��PB,PE�˿�ʱ��,�����̲��õ���ϵͳ��λ��Ĭ�ϵ��ڲ�ʱ��HSI,��8MHz��RCʱ�ӡ� 

  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;				       //����ʹ��GPIO�ܽ�PB.5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		       //����GPIOģʽ��ͨ���������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		       //����GPIO�˿����ʡ�����������Ϊ50MHz
  GPIO_Init(LED1_GPIO, &GPIO_InitStructure);					       //�����趨������ʼ��GPIOB.5
  GPIO_SetBits(GPIOB,GPIO_Pin_5);						               //PB.5�����,�ر�LED0

  GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;	    		     //PE.5 �˿�����, �������
  GPIO_Init(LED2_GPIO, &GPIO_InitStructure);	  				     //���������IO���ٶ�Ϊ50MHz
  GPIO_SetBits(GPIOE,GPIO_Pin_5); 						             //PE.5����� 
}
