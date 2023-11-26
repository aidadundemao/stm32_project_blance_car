#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "MyI2C.h"
#include "Motor.h"


int main(void)
{
	Motor_Init();

    Motor_SetSpeed1(50);

    Motor_SetSpeed2(20);

    while (1)
    {

	}
}
