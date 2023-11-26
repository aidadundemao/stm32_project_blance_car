/* 
	 led.h文件功能：(1)LED 灯引脚宏定义；(2)控制 LED 灯亮灭状态的宏定义。
	 在编写应用程序的过程中，要考虑更改硬件环境的情况。例如 LED 灯的控制引脚与当
前的不一样，我们希望程序只需要做最小的修改即可在新的环境正常运行，这个时候一般
把硬件相关的部分使用宏来封装。若更改了硬件环境，只修改这些硬件相关的宏即可，这
些定义一般存储在头文件，即本例子中的“led.h”文件中。
   为了方便控制 LED 灯，我们把 LED 灯常用的亮、灭及状态反转的控制也直接定义成宏。
*/	
	#ifndef __led_h                                          //它的功能是防止头文件被重复包含，避免引起编译错误
  #define __led_h                                          //它的功能是防止头文件被重复包含，避免引起编译错误
 
 #include "stm32f10x.h"

/*专门把这些与开发板硬件相关的内容定义为宏，这对于修改或者移植程序非常方便。*/
  /*---LED灯引脚宏定义---*/
#define LED1_GPIO              GPIOB                                                      //GPIO端口宏定义
#define LED1_GPIO_PIN          GPIO_Pin_5                                                 //GPIO引脚号宏定义,连接红色led

#define LED2_GPIO              GPIOE                                                      //GPIO引脚号宏定义,连接绿色led
#define LED2_GPIO_PIN          GPIO_Pin_5                                                 

/*---控制LED灯亮灭状态的宏定义---*/
#define LED1_ON                GPIO_ResetBits(LED1_GPIO,LED1_GPIO_PIN)                   //LED0对应引脚GPIOB.5拉低，亮  等同LED0=0;
#define LED1_OFF               GPIO_SetBits(LED1_GPIO,LED1_GPIO_PIN)	                    //LED0对应引脚GPIOB.5拉高，灭  等同LED0=1;

#define LED2_ON                GPIO_ResetBits(LED2_GPIO,LED2_GPIO_PIN)                   //LED1对应引脚GPIOE.5拉低，亮 等同LED1=0;
#define LED2_OFF               GPIO_SetBits(LED2_GPIO,LED2_GPIO_PIN)                     //LED1对应引脚GPIOE.5拉高，灭 等同LED1=1;


/*--读取LED两边的状态--*/
#define LED1_Status            GPIO_ReadInputDataBit(LED1_GPIO,LED1_GPIO_PIN)
#define LED2_Status            GPIO_ReadInputDataBit(LED2_GPIO,LED2_GPIO_PIN)


/*--控制LED灯电平翻转的的宏定义*/
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

void GPIO_LED_Init(void);                                                                //GPIO口初始化声明（含打开相应时钟）

/*
  以上代码分别把控制 LED 灯的 GPIO 端口、GPIO 引脚号以及 GPIO 端口时钟封装起来了。
在实际控制的时候我们就直接用这些宏，以达到应用代码跟硬件无关的效果。
*/

 	#endif                                                                                    //它的功能是防止头文件被重复包含，避免引起编译错误
	
