
#include "led.h"
/*******************************************************************************
 函数名称: GPIO_LED_Init
 函数说明: GPIO口初始化函数 
 输入参数: 无  
 返 回 值: 无  
*******************************************************************************/
void GPIO_LED_Init(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;	                     //定义一个结构体变量GPIO_InitStructure
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);//使能PB,PE端口时钟,本工程采用的是系统复位后默认的内部时钟HSI,即8MHz的RC时钟。 

  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;				       //配置使能GPIO管脚PB.5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		       //配置GPIO模式—通用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		       //配置GPIO端口速率—最高输出速率为50MHz
  GPIO_Init(LED1_GPIO, &GPIO_InitStructure);					       //根据设定参数初始化GPIOB.5
  GPIO_SetBits(GPIOB,GPIO_Pin_5);						               //PB.5输出高,关闭LED0

  GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;	    		     //PE.5 端口配置, 推挽输出
  GPIO_Init(LED2_GPIO, &GPIO_InitStructure);	  				     //推挽输出，IO口速度为50MHz
  GPIO_SetBits(GPIOE,GPIO_Pin_5); 						             //PE.5输出高 
}
