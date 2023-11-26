#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Timer.h"
#include "Encoder.h"
extern uint16_t num;
uint16_t speed;
int main(void)
{
    OLED_Init();
	Motor_Init();
    Encoder_Init();
    Timer_Init();
    Motor_SetSpeed1(10);
    Motor_SetSpeed2(10);

    while (1)
    {
        speed = 1000 * num * 0.00418876;
        OLED_ShowString(1,0,"SPEED:");
        OLED_ShowNum(1,6,speed,5);
        OLED_ShowString(1,11,"M/S");
	}
}
