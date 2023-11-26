
#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "string.h"

extern uint8_t receiveFinish;
extern uint8_t receiveData[255];
/*******************************************************************************
 函数名称: main
 函数说明: 主函数 
 输    入: 无
 返 回 值: 无
*******************************************************************************/
int main(void)
{
    GPIO_USART1_Init(115200);	                                       //初始化串口USART1
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	                 //中断分组2
    uint8_t key=0;	
    GPIO_LED_Init();			                                           //LED端口初始化
    GPIO_KEY_Init();                                                 //初始化与按键连接的硬件接口
    GPIO_BEEP_Init();                                   	           //初始化蜂鸣器端口
    printf("姓名：%s，学号：%s\r\n\r\n按键 KEY0 控制红色的DS0和绿色的DS1，按一次，他们的状态就翻转一次。\r\n按键 KEY1 控制绿色的DS1，按一次亮，再按一次灭。\r\n按键 KEY2 控制红色的DS0，按一次亮，再按一次灭。\r\n按键 WK_UP 控制蜂鸣器，按一次叫，再按一次停。\r\n\r\n串口助手发送一次%s01，红色的DS0和绿色的DS1的状态就翻转一次。\r\n串口助手发送一次%s02，绿色的DS1亮灭就交换一次。\r\n串口助手发送一次%s03，红色的DS0亮灭就交换一次。\r\n串口助手发送一次%s04，蜂鸣器鸣停就交换一次.\r\n","罗绍林","202116067205","05","05","05","05");
    while(1)
    {
          key=KEY_Scan(0);	                                             //得到键值
          if(key)
            {						   
                switch(key)
                {				  
                    case WKUP_PRES: BEEP_Trigger;    printf("\r\n按键操作成功，鸣器状态翻转\r\n"); break;           //按键 WK_UP 控制蜂鸣器，按一次叫，再按一次停             
                    case KEY2_PRES: RedLed;          printf("\r\n按键操作成功，绿灯状态翻转\r\n"); break;                //按键 KEY2 控制红色的DS0，按一次亮，再按一次灭。             
                    case KEY1_PRES: GreenLed;        printf("\r\n按键操作成功，绿灯状态翻转\r\n"); break;             //按键 KEY1 控制绿色的DS1，按一次亮，再按一次灭            
                    case KEY0_PRES: RedLed; GreenLed;printf("\r\n按键操作成功，绿灯和红灯状态翻转\r\n"); break;          //按键 KEY0 控制红色的DS0和绿色的DS1，按一次，他们的状态就翻转一次。                 
                }
            }
            
           if(receiveFinish==1)									                         //数据结束标志
            {
                receiveFinish = 0;                
                if(receiveData[0] == '0' && receiveData[1] == '5' && receiveData[2] == '0'&& ( receiveData[3] == '1' || receiveData[3] == '2' || receiveData[3] == '3' || receiveData[3] == '4'))
                {
                    switch(receiveData[3])
                    {				  
                        case '1': RedLed; GreenLed; printf("\r\n串口发送成功，红灯与绿灯状态翻转\r\n");break;                            
                        case '2': GreenLed;         printf("\r\n串口发送成功，绿灯状态翻转\r\n");      break;                 
                        case '3': RedLed;           printf("\r\n串口发送成功，红灯状态翻转\r\n");      break;                 
                        case '4': BEEP_Trigger;     printf("\r\n串口发送成功，蜂鸣器状态翻转\r\n");    break;
                    }
                    
                }
                 else
               {  
                  printf("\r\n\r\n输入有误，重新输入指令\r\n\r\n\r\n\r\n\r\n\r\n");
                  printf("姓名：%s，学号：%s\r\n\r\n按键 KEY0 控制红色的DS0和绿色的DS1，按一次，他们的状态就翻转一次。\r\n按键 KEY1 控制绿色的DS1，按一次亮，再按一次灭。\r\n按键 KEY2 控制红色的DS0，按一次亮，再按一次灭。\r\n按键 WK_UP 控制蜂鸣器，按一次叫，再按一次停。\r\n\r\n串口助手发送一次%s01，红色的DS0和绿色的DS1的状态就翻转一次。\r\n串口助手发送一次%s02，绿色的DS1亮灭就交换一次。\r\n串口助手发送一次%s03，红色的DS0亮灭就交换一次。\r\n串口助手发送一次%s04，蜂鸣器鸣停就交换一次.\r\n","罗绍林","202116067205","05","05","05","05");

               }
                                  
         } 
    }	 

     
}
