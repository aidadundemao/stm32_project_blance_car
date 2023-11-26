
#include "usart.h"
uint8_t receiveData[255]={0};
uint8_t receiveFinish=0;
/*******************************************************************************
 ��������: USART1_Configuration
 ����˵��: ����USART1��ʼ������ 
 ��    ��: �β�BaudRate(������)
 �� �� ֵ: ��
*******************************************************************************/
void GPIO_USART1_Init(uint32_t BaudRate)							                       
{																
  GPIO_InitTypeDef GPIO_InitStructure;			           		   	    //����GPIO�ܽų�ʼ���ṹ��
  USART_InitTypeDef USART_InitStructure;							            //���崮�ڳ�ʼ���ṹ��
	NVIC_InitTypeDef  NVIC_InitStructure;                           //�����ж�������ʼ���ṹ��
		
	/*-----��GPIO��ʱ�Ӻʹ���ʱ��-----*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);            //ʹ��(��)GPIOA�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);           //ʹ��USART1��ʱ��

	/*-----��ʼ��I/O��(���ڴ���ͨ������)-----*/
  //Configure USART1 Tx (PA.09) as alternate function push-pull
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			                  //ѡ�д���Ĭ�Ϲܽ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                //����ܽ�9��ģʽ�������������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		            //��������������
  GPIO_Init(GPIOA, &GPIO_InitStructure);			                    //���ú������Խṹ��������г�ʼ��
  //Configure USART1 Rx (PA.10) as input floating		         
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	                    //ѡ�д���Ĭ�Ϲܽ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			      //����ܽ�10��ģʽ����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);						              //���ú������Խṹ��������г�ʼ��

	/*-----���ڳ�ʼ������-----*/
  USART_InitStructure.USART_BaudRate = BaudRate;			           	//���ô���ͨ��ʱ������BaudRate,��ֵ���������ȷ��
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;		  //��������λ�ĳ���8��λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	        //����1��ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No ;	          //����У��λ���ޡ�
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//����Ӳ��������ʧ��
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//���÷���ʹ�ܡ�����ʹ��
  USART_Init(USART1, &USART_InitStructure);	                      //�����ϸ���ֵ�Ľṹ����г�ʼ��
    
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                    //ʹ��(����)���ڽ����жϹ���
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);                    //ʹ�ܴ��ڿ��������ж�
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			                        					

	/*-----ʹ�ܴ���(�򿪴���)-----*/
  USART_Cmd(USART1, ENABLE);			                                //����USART1,ע��������RCC_APB2PeriphClockCmd()���õ�����
}
/*************************************************************************
�� �� �� : USART1_IRQHandler
�������� : ����1�жϺ���(�������ж�+�����жϡ�������ɽ���һ֡������������)
������� : ��
�� �� ֵ : ��
*************************************************************************/
void USART1_IRQHandler()
{
	static uint32_t rev_cnt = 0;                                //����һ����������,��̬�ֲ�����
	uint8_t ch;
	/*----------------���ڽ����ж�------------------*/
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)            //���յ�һ���ֽڣ�����һ�ν����ж�  
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);            //��������жϱ�־λ,Ϊ��һ��"�����ж�"������׼��
		ch = USART_ReceiveData(USART1);                           //�ȼ���ch = USART1->DR;��ȡ���յ�������
		receiveData[rev_cnt++] = ch;
	}
	else if(USART_GetITStatus(USART1,USART_IT_IDLE)==SET)  		  //IDLE�ж�
	{
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);		        //���IDLE��ʶ
		ch = USART_ReceiveData(USART1);						                //USART1->DR����DR����ɶ�idle�жϵ�����,�����һֱ�����ж�
    /*--�����ַ�������������ֹ��ʾ�ϴθ���������---*/
		receiveData[rev_cnt]='\0'; 
		receiveFinish=1;                                          //����һ��������ɵı���receiveFinish��1
		/*-----���ռ����������㣬Ϊ��һ�ֽ�����׼��----*/
		rev_cnt = 0;
	}
}
/*************************************************************************
�������ƣ� Uart1_sendBytes
����˵���� ������ֽڵ����ݷ��ͳ�ȥ
�������: ָ��pRxBuf��ָ���ַ��Ԫ������
�� �� ֵ: ��
*************************************************************************/
void Uart1_sendBytes(uint8_t *pRxBuf)
{
  while(*pRxBuf != '\0')
  {
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET )  //���ǰһ�������Ƿ�����
    {
       ;                                                       //�ȴ��������
    }
    USART_SendData(USART1,*pRxBuf);                            //����1���ֽڵ�����,��USART1->DR = *pRxBuf; 		
    pRxBuf++;                                                  //ָ����һ����Ԫ
  }
}
/*******************************************************************************
 ��������: fputc
 ����˵��: �ض���putc��������������ʹ��printf�����Ӵ���1��ӡ���������
 �������: ��
 �� �� ֵ: ��
*******************************************************************************/
int fputc(int ch,FILE *p)                                         //����Ĭ�ϵ� ��ʹ��printf����ʱ�Զ�����
{
	USART_SendData(USART1,(uint8_t)ch);	                            //дһ���ֽڵ�USART
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}
//int fputc(int ch,FILE *f)											                  //�ض���fputc������ͬ����ĺ����ǵȼ۵�
//{
//	while((USART1->SR & 0x40) == 0);
//	USART1->DR = (u8)ch;
//	return ch;
//}
/*******************************************************************************
 ��������: fputc
 ����˵��: �ض���getc��������������ʹ��scanff�����Ӵ���1��������
 �������: ��
 �� �� ֵ: ��
*******************************************************************************/
int fgetc(FILE *f) 
{ 	
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);   //�ȴ�����1��������
	return (int)USART_ReceiveData(USART1); 
}
