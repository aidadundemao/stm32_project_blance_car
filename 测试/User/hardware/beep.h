
#ifndef __beep_h
#define __beep_h	 

#include "stm32f10x.h"
#include "mydelay.h"
   
#define BEEP_GPIO              GPIOB                                                      //GPIO端口宏定义
#define BEEP_GPIO_PIN          GPIO_Pin_8

#define BEEP_ON         GPIO_SetBits(BEEP_GPIO,BEEP_GPIO_PIN)                           //BEEP开启
#define BEEP_OFF        GPIO_ResetBits(BEEP_GPIO,BEEP_GPIO_PIN)                         //BEEP关闭
                                                                                     
                                                                                     
                                                                                     //鸣叫250毫秒
#define DEEP            do{\
                         BEEP_ON;delay_ms(250);BEEP_OFF;\
                        }while(0)

  /*--读取LED两边的状态--*/
#define BEEP_Status        GPIO_ReadInputDataBit(BEEP_GPIO,BEEP_GPIO_PIN)



/*--控制LED灯电平翻转的的宏定义*/
#define BEEP_Trigger do{if(BEEP_Status)\
                            BEEP_OFF;\
                        else\
                            BEEP_ON;\
                        }while(0)

void GPIO_BEEP_Init(void);	//初始化
                                
#endif

