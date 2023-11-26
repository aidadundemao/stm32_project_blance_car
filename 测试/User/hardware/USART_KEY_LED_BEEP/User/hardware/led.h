/* 
	 led.h�ļ����ܣ�(1)LED �����ź궨�壻(2)���� LED ������״̬�ĺ궨�塣
	 �ڱ�дӦ�ó���Ĺ����У�Ҫ���Ǹ���Ӳ����������������� LED �ƵĿ��������뵱
ǰ�Ĳ�һ��������ϣ������ֻ��Ҫ����С���޸ļ������µĻ����������У����ʱ��һ��
��Ӳ����صĲ���ʹ�ú�����װ����������Ӳ��������ֻ�޸���ЩӲ����صĺ꼴�ɣ���
Щ����һ��洢��ͷ�ļ������������еġ�led.h���ļ��С�
   Ϊ�˷������ LED �ƣ����ǰ� LED �Ƴ��õ�������״̬��ת�Ŀ���Ҳֱ�Ӷ���ɺꡣ
*/	
	#ifndef __led_h                                          //���Ĺ����Ƿ�ֹͷ�ļ����ظ���������������������
  #define __led_h                                          //���Ĺ����Ƿ�ֹͷ�ļ����ظ���������������������
 
 #include "stm32f10x.h"

/*ר�Ű���Щ�뿪����Ӳ����ص����ݶ���Ϊ�꣬������޸Ļ�����ֲ����ǳ����㡣*/
  /*---LED�����ź궨��---*/
#define LED1_GPIO              GPIOB                                                      //GPIO�˿ں궨��
#define LED1_GPIO_PIN          GPIO_Pin_5                                                 //GPIO���źź궨��,���Ӻ�ɫled

#define LED2_GPIO              GPIOE                                                      //GPIO���źź궨��,������ɫled
#define LED2_GPIO_PIN          GPIO_Pin_5                                                 

/*---����LED������״̬�ĺ궨��---*/
#define LED1_ON                GPIO_ResetBits(LED1_GPIO,LED1_GPIO_PIN)                   //LED0��Ӧ����GPIOB.5���ͣ���  ��ͬLED0=0;
#define LED1_OFF               GPIO_SetBits(LED1_GPIO,LED1_GPIO_PIN)	                    //LED0��Ӧ����GPIOB.5���ߣ���  ��ͬLED0=1;

#define LED2_ON                GPIO_ResetBits(LED2_GPIO,LED2_GPIO_PIN)                   //LED1��Ӧ����GPIOE.5���ͣ��� ��ͬLED1=0;
#define LED2_OFF               GPIO_SetBits(LED2_GPIO,LED2_GPIO_PIN)                     //LED1��Ӧ����GPIOE.5���ߣ��� ��ͬLED1=1;


/*--��ȡLED���ߵ�״̬--*/
#define LED1_Status            GPIO_ReadInputDataBit(LED1_GPIO,LED1_GPIO_PIN)
#define LED2_Status            GPIO_ReadInputDataBit(LED2_GPIO,LED2_GPIO_PIN)


/*--����LED�Ƶ�ƽ��ת�ĵĺ궨��*/
#define LED1_Trigger do{if(LED1_Status)\
                          LED1_ON;\
                        else\
                          LED1_OFF;\
                        }while(0)
#define LED2_Trigger do{if(LED2_Status)\
                          LED2_ON;\
                        else\
                          LED2_OFF;\
                        }while(0)

#define RedLed   LED1_Trigger
#define GreenLed LED2_Trigger

void GPIO_LED_Init(void);                                                                //GPIO�ڳ�ʼ��������������Ӧʱ�ӣ�

/*
  ���ϴ���ֱ�ѿ��� LED �Ƶ� GPIO �˿ڡ�GPIO ���ź��Լ� GPIO �˿�ʱ�ӷ�װ�����ˡ�
��ʵ�ʿ��Ƶ�ʱ�����Ǿ�ֱ������Щ�꣬�ԴﵽӦ�ô����Ӳ���޹ص�Ч����
*/

 	#endif                                                                                    //���Ĺ����Ƿ�ֹͷ�ļ����ظ���������������������
	
