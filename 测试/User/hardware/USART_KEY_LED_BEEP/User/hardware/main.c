
#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "string.h"

extern uint8_t receiveFinish;
extern uint8_t receiveData[255];
/*******************************************************************************
 ��������: main
 ����˵��: ������ 
 ��    ��: ��
 �� �� ֵ: ��
*******************************************************************************/
int main(void)
{
    GPIO_USART1_Init(115200);	                                       //��ʼ������USART1
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	                 //�жϷ���2
    uint8_t key=0;	
    GPIO_LED_Init();			                                           //LED�˿ڳ�ʼ��
    GPIO_KEY_Init();                                                 //��ʼ���밴�����ӵ�Ӳ���ӿ�
    GPIO_BEEP_Init();                                   	           //��ʼ���������˿�
    printf("������%s��ѧ�ţ�%s\r\n\r\n���� KEY0 ���ƺ�ɫ��DS0����ɫ��DS1����һ�Σ����ǵ�״̬�ͷ�תһ�Ρ�\r\n���� KEY1 ������ɫ��DS1����һ�������ٰ�һ����\r\n���� KEY2 ���ƺ�ɫ��DS0����һ�������ٰ�һ����\r\n���� WK_UP ���Ʒ���������һ�νУ��ٰ�һ��ͣ��\r\n\r\n�������ַ���һ��%s01����ɫ��DS0����ɫ��DS1��״̬�ͷ�תһ�Ρ�\r\n�������ַ���һ��%s02����ɫ��DS1����ͽ���һ�Ρ�\r\n�������ַ���һ��%s03����ɫ��DS0����ͽ���һ�Ρ�\r\n�������ַ���һ��%s04����������ͣ�ͽ���һ��.\r\n","������","202116067205","05","05","05","05");
    while(1)
    {
          key=KEY_Scan(0);	                                             //�õ���ֵ
          if(key)
            {						   
                switch(key)
                {				  
                    case WKUP_PRES: BEEP_Trigger;    printf("\r\n���������ɹ�������״̬��ת\r\n"); break;           //���� WK_UP ���Ʒ���������һ�νУ��ٰ�һ��ͣ             
                    case KEY2_PRES: RedLed;          printf("\r\n���������ɹ����̵�״̬��ת\r\n"); break;                //���� KEY2 ���ƺ�ɫ��DS0����һ�������ٰ�һ����             
                    case KEY1_PRES: GreenLed;        printf("\r\n���������ɹ����̵�״̬��ת\r\n"); break;             //���� KEY1 ������ɫ��DS1����һ�������ٰ�һ����            
                    case KEY0_PRES: RedLed; GreenLed;printf("\r\n���������ɹ����̵ƺͺ��״̬��ת\r\n"); break;          //���� KEY0 ���ƺ�ɫ��DS0����ɫ��DS1����һ�Σ����ǵ�״̬�ͷ�תһ�Ρ�                 
                }
            }
            
           if(receiveFinish==1)									                         //���ݽ�����־
            {
                receiveFinish = 0;                
                if(receiveData[0] == '0' && receiveData[1] == '5' && receiveData[2] == '0'&& ( receiveData[3] == '1' || receiveData[3] == '2' || receiveData[3] == '3' || receiveData[3] == '4'))
                {
                    switch(receiveData[3])
                    {				  
                        case '1': RedLed; GreenLed; printf("\r\n���ڷ��ͳɹ���������̵�״̬��ת\r\n");break;                            
                        case '2': GreenLed;         printf("\r\n���ڷ��ͳɹ����̵�״̬��ת\r\n");      break;                 
                        case '3': RedLed;           printf("\r\n���ڷ��ͳɹ������״̬��ת\r\n");      break;                 
                        case '4': BEEP_Trigger;     printf("\r\n���ڷ��ͳɹ���������״̬��ת\r\n");    break;
                    }
                    
                }
                 else
               {  
                  printf("\r\n\r\n����������������ָ��\r\n\r\n\r\n\r\n\r\n\r\n");
                  printf("������%s��ѧ�ţ�%s\r\n\r\n���� KEY0 ���ƺ�ɫ��DS0����ɫ��DS1����һ�Σ����ǵ�״̬�ͷ�תһ�Ρ�\r\n���� KEY1 ������ɫ��DS1����һ�������ٰ�һ����\r\n���� KEY2 ���ƺ�ɫ��DS0����һ�������ٰ�һ����\r\n���� WK_UP ���Ʒ���������һ�νУ��ٰ�һ��ͣ��\r\n\r\n�������ַ���һ��%s01����ɫ��DS0����ɫ��DS1��״̬�ͷ�תһ�Ρ�\r\n�������ַ���һ��%s02����ɫ��DS1����ͽ���һ�Ρ�\r\n�������ַ���һ��%s03����ɫ��DS0����ͽ���һ�Ρ�\r\n�������ַ���һ��%s04����������ͣ�ͽ���һ��.\r\n","������","202116067205","05","05","05","05");

               }
                                  
         } 
    }	 

     
}
