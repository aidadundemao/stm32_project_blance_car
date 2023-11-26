
#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "MPU6050.h"

uint8_t ID;
//int16_t AX, AY, AZ, GX, GY, GZ;
/*******************************************************************************
 函数名称: main
 函数说明: 主函数 
 输    入: 无
 返 回 值: 无
*******************************************************************************/
int main(void)
{
    GPIO_USART1_Init(115200);	                                       //初始化串口USART1
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //中断分组2
    
    MPU6050_Init();

	ID = MPU6050_GetID();
    printf("ID:%d" ,ID);
    while(1)
    {
          
    }	 

     
}
