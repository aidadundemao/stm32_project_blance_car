
#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "MPU6050.h"
#include "MyI2C.h"
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
    MyI2C_Init();
    
    MyI2C_Start();
    MyI2C_SendByte(0XD2);
    uint8_t Ack = MyI2C_ReceiveAck();
    MyI2C_Stop();
    
   // OLED_ShowNum(1,1,Ack,3);
    printf("Ack:%d" ,Ack);
    while(1)
    {
          
    }	 

     
}
