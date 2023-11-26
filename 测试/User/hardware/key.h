 
#ifndef __key_h
#define __key_h	 
 
#define KEY0    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)       //��ȡ����KEY0
#define KEY1    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)       //��ȡ����KEY1
#define KEY2    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)       //��ȡ����KEY2 
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)       //��ȡ����WK_UP 

 

#define KEY0_PRES 	  1	                                        //KEY0����
#define KEY1_PRES	  2	                                        //KEY1����
#define KEY2_PRES	  3	                                        //KEY2����
#define WKUP_PRES     4	                                        //KEY_UP����(��WK_UP/KEY_UP)


void GPIO_KEY_Init(void);                                     //�밴��������IO��ʼ��
uint8_t KEY_Scan(uint8_t mode);  	                            //����ɨ�躯��			

#endif
