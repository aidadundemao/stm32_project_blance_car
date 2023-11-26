
#include "usart.h"
uint8_t receiveData[255]={0};
uint8_t receiveFinish=0;
/*******************************************************************************
 函数名称: USART1_Configuration
 函数说明: 串口USART1初始化函数 
 输    入: 形参BaudRate(波特率)
 返 回 值: 无
*******************************************************************************/
void GPIO_USART1_Init(uint32_t BaudRate)							                       
{																
  GPIO_InitTypeDef GPIO_InitStructure;			           		   	    //定义GPIO管脚初始化结构体
  USART_InitTypeDef USART_InitStructure;							            //定义串口初始化结构体
	NVIC_InitTypeDef  NVIC_InitStructure;                           //定义中断向量初始化结构体
		
	/*-----打开GPIO口时钟和串口时钟-----*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);            //使能(打开)GPIOA端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);           //使能USART1的时钟

	/*-----初始化I/O口(用于串行通信引脚)-----*/
  //Configure USART1 Tx (PA.09) as alternate function push-pull
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			                  //选中串口默认管脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                //定义管脚9的模式：复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		            //定义输出最大速率
  GPIO_Init(GPIOA, &GPIO_InitStructure);			                    //调用函数，对结构体参数进行初始化
  //Configure USART1 Rx (PA.10) as input floating		         
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	                    //选中串口默认管脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			      //定义管脚10的模式：浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);						              //调用函数，对结构体参数进行初始化

	/*-----串口初始化设置-----*/
  USART_InitStructure.USART_BaudRate = BaudRate;			           	//设置串口通信时波特率BaudRate,其值由输入参数确定
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;		  //设置数据位的长度8个位
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	        //设置1个停止位
  USART_InitStructure.USART_Parity = USART_Parity_No ;	          //设置校验位“无”
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//设置硬件控制流失能
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//设置发送使能、接收使能
  USART_Init(USART1, &USART_InitStructure);	                      //对以上赋完值的结构体进行初始化
    
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                    //使能(开启)串口接收中断功能
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);                    //使能串口空闲总线中断
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);			                        					

	/*-----使能串口(打开串口)-----*/
  USART_Cmd(USART1, ENABLE);			                                //开启USART1,注意与上面RCC_APB2PeriphClockCmd()设置的区别
}
/*************************************************************************
函 数 名 : USART1_IRQHandler
函数功能 : 串口1中断函数(“接收中断+空闲中断”可以完成接收一帧不定长的数据)
输入参数 : 无
返 回 值 : 无
*************************************************************************/
void USART1_IRQHandler()
{
	static uint32_t rev_cnt = 0;                                //定义一个计数变量,静态局部变量
	uint8_t ch;
	/*----------------串口接收中断------------------*/
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)            //接收到一个字节，进入一次接收中断  
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);            //清除接收中断标志位,为下一次"接收中断"发生做准备
		ch = USART_ReceiveData(USART1);                           //等价于ch = USART1->DR;读取接收到的数据
		receiveData[rev_cnt++] = ch;
	}
	else if(USART_GetITStatus(USART1,USART_IT_IDLE)==SET)  		  //IDLE中断
	{
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);		        //清除IDLE标识
		ch = USART_ReceiveData(USART1);						                //USART1->DR，读DR以完成对idle中断的清零,否则会一直进入中断
    /*--加入字符串结束符，防止显示上次更长的数据---*/
		receiveData[rev_cnt]='\0'; 
		receiveFinish=1;                                          //代表一包数据完成的变量receiveFinish置1
		/*-----接收计数变量清零，为新一轮接收做准备----*/
		rev_cnt = 0;
	}
}
/*************************************************************************
函数名称： Uart1_sendBytes
函数说明： 将多个字节的数据发送出去
输入参数: 指针pRxBuf所指向地址单元的数据
返 回 值: 无
*************************************************************************/
void Uart1_sendBytes(uint8_t *pRxBuf)
{
  while(*pRxBuf != '\0')
  {
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET )  //检测前一个数据是否发送完
    {
       ;                                                       //等待发送完成
    }
    USART_SendData(USART1,*pRxBuf);                            //发送1个字节的数据,或USART1->DR = *pRxBuf; 		
    pRxBuf++;                                                  //指向下一个单元
  }
}
/*******************************************************************************
 函数名称: fputc
 函数说明: 重定义putc函数，这样可以使用printf函数从串口1打印输出化函数
 输入参数: 无
 返 回 值: 无
*******************************************************************************/
int fputc(int ch,FILE *p)                                         //函数默认的 在使用printf函数时自动调用
{
	USART_SendData(USART1,(uint8_t)ch);	                            //写一个字节到USART
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}
//int fputc(int ch,FILE *f)											                  //重定向fputc函数，同上面的函数是等价的
//{
//	while((USART1->SR & 0x40) == 0);
//	USART1->DR = (u8)ch;
//	return ch;
//}
/*******************************************************************************
 函数名称: fputc
 函数说明: 重定义getc函数，这样可以使用scanff函数从串口1输入数据
 输入参数: 无
 返 回 值: 无
*******************************************************************************/
int fgetc(FILE *f) 
{ 	
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);   //等待串口1输入数据
	return (int)USART_ReceiveData(USART1); 
}
