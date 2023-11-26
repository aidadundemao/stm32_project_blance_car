/****************************************
 ���ܣ�����ͳһ��װ�����˿�������
*****************************************/
#ifndef __GPIO_H
#define __GPIO_H
#include "stm32f10x.h"                  // Device header

/**
  * ESP8266
*/
#define ESP8266_TX_GPIO GPIOA
#define ESP8266_TX_GPIO_PIN GPIO_Pin_3

#define ESP8266_RX_GPIO GPIOA
#define ESP8266_RX_GPIO_PIN GPIO_Pin_2


/**
  * OLED ��ʾ
*/
#define OLED_SCL_GPIO GPIOB
#define OLED_SCL_GPIO_PIN GPIO_Pin_10

#define OLED_SDA_GPIO GPIOB
#define OLED_SDA_GPIO_PIN GPIO_Pin_11


/**
  * MPU6050
*/
#define MPU_SCL_GPIO GPIOA
#define MPU_SCL_GPIO_PIN GPIO_Pin_12

#define MPU_SDA_GPIO GPIOA
#define MPU_SDA_GPIO_PIN GPIO_Pin_11


/**
  *������
*/
#define ECHO_GPIO GPIOA
#define ECHO_GPIO_PIN GPIO_Pin_8

#define TRING_GPIO GPIOB
#define TRING_GPIO_PIN GPIO_Pin_15 


/**
  * ���Ƶ�����������
*/
#define AIN1_GPIO  GPIOB
#define AIN1_GPIO_PIN GPIO_Pin_0
#define AIN2_GPIO  GPIOB
#define AIN2_GPIO_PIN GPIO_Pin_1

#define BIN1_GPIO  GPIOB
#define BIN1_GPIO_PIN GPIO_Pin_8
#define BIN2_GPIO  GPIOB
#define BIN2_GPIO_PIN GPIO_Pin_9

#define AIN1(x) do{ x ?\
                    GPIO_SetBits(AIN1_GPIO, AIN1_GPIO_PIN):\
                    GPIO_ResetBits(AIN1_GPIO, AIN1_GPIO_PIN);\
                   }while(0)

#define AIN2(x) do{ x ?\
                    GPIO_SetBits(AIN2_GPIO, AIN2_GPIO_PIN):\
                    GPIO_ResetBits(AIN2_GPIO, AIN2_GPIO_PIN);\
                   }while(0)

#define BIN1(x) do{ x ?\
                    GPIO_SetBits(BIN1_GPIO, BIN1_GPIO_PIN):\
                    GPIO_ResetBits(BIN1_GPIO, BIN1_GPIO_PIN);\
                   }while(0)

#define BIN2(x) do{ x ?\
                    GPIO_SetBits(BIN2_GPIO, BIN2_GPIO_PIN):\
                    GPIO_ResetBits(BIN2_GPIO, BIN2_GPIO_PIN);\
                   }while(0)                   
/**
  *��������PWM�Ķ˿�������
*/
#define PWMA_GPIO  GPIOA
#define PWMA_GPIO_PIN GPIO_Pin_0
#define PWMB_GPIO  GPIOA
#define PWMB_GPIO_PIN GPIO_Pin_1
 

#endif
