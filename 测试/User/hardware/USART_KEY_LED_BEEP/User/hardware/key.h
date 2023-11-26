 
#ifndef __key_h
#define __key_h	 
 
#define KEY0    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)       //读取按键KEY0
#define KEY1    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)       //读取按键KEY1
#define KEY2    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)       //读取按键KEY2 
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)       //读取按键WK_UP 

 

#define KEY0_PRES 	  1	                                        //KEY0按下
#define KEY1_PRES	  2	                                        //KEY1按下
#define KEY2_PRES	  3	                                        //KEY2按下
#define WKUP_PRES     4	                                        //KEY_UP按下(即WK_UP/KEY_UP)


void GPIO_KEY_Init(void);                                     //与按键相连的IO初始化
uint8_t KEY_Scan(uint8_t mode);  	                            //按键扫描函数			

#endif
