    
	一、实验器材
	战舰STM32F103开发板V3版本。
	
	二、硬件资源
	1.DS0(连接在PB5),DS1(连接在PE5)
	2.蜂鸣器(连接在PB8)
	3.按键KEY0(PE4)/KEY1(PE3)/KEY2(PE2)/KEY_UP(PA0,也称之为WK_UP)
	4.排针P4由短路块把PA10与TXD、PA9与RXD分别连通；由数据线把开发板上的USB_232接口与电脑USB口相
连。注意：需先安装“开发板USB转串口CH340驱动软件CH341SER.EXE”软件。
	
	三、实验目的
	熟悉串口的printf功能，其原理参考“安富莱_STM32-V5开发板_用户手册（V2.0） ”第286页说明。
	
	四、本项目的功能
	通过fputc()函数实现串口的printf打印功能，通过串口显示四个按键KEY0、KEY1、KEY2
、KEY3哪一个被按下，以及对应LED灯或蜂鸣器的状态。
    实现USART的printf功能只要做好两个工作就可以了：一个是串口的初始化，另一个就是两个函数fputc()、
fgetc()的重定向。
    注意， 打开“魔法棒”之后，在“Target”界面上在“MicroLib”之前的方框内打勾，即使能。
	
	五、串口初始化的四大步骤
	(1)初始化I/O口(用于串行通信引脚)。函数GPIO_Init()
	(2)打开GPIO口时钟和串口时钟。函数RCC_APB2PeriphClockCmd()
	(3)串口初始化设置。函数USART_Init()
	(4)使能串口,即开启串口功能。函数USART_Cmd()