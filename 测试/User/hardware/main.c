
#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "MPU6050.h"

uint8_t ID;
//int16_t AX, AY, AZ, GX, GY, GZ;
/*******************************************************************************
 ��������: main
 ����˵��: ������ 
 ��    ��: ��
 �� �� ֵ: ��
*******************************************************************************/
int main(void)
{
    GPIO_USART1_Init(115200);	                                       //��ʼ������USART1
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //�жϷ���2
    
    MPU6050_Init();

	ID = MPU6050_GetID();
    printf("ID:%d" ,ID);
    while(1)
    {
          
    }	 

     
}
