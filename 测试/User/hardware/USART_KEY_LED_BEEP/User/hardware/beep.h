
#ifndef __beep_h
#define __beep_h	 

#include "stm32f10x.h"
#include "mydelay.h"
   
#define BEEP_GPIO              GPIOB                                                      //GPIO�˿ں궨��
#define BEEP_GPIO_PIN          GPIO_Pin_8

#define BEEP_ON         GPIO_SetBits(BEEP_GPIO,BEEP_GPIO_PIN)                           //BEEP����
#define BEEP_OFF        GPIO_ResetBits(BEEP_GPIO,BEEP_GPIO_PIN)                         //BEEP�ر�
                                                                                     
                                                                                     
                                                                                     //����250����
#define DEEP            do{\
                         BEEP_ON;delay_ms(250);BEEP_OFF;\
                        }while(0)

  /*--��ȡLED���ߵ�״̬--*/
#define BEEP_Status        GPIO_ReadInputDataBit(BEEP_GPIO,BEEP_GPIO_PIN)



/*--����LED�Ƶ�ƽ��ת�ĵĺ궨��*/
#define BEEP_Trigger do{if(BEEP_Status)\
                            BEEP_OFF;\
                        else\
                            BEEP_ON;\
                        }while(0)

void GPIO_BEEP_Init(void);	//��ʼ��
                                
#endif

