#include "mydelay.h"

void delay_us(u16 nus)
{
    u16 i=0;  
    while(nus--)
    {
        i=8;  //������Ƶ����
        while(i--);    
    }
}

void delay_ms(u16 nms)
{
    u16 i=0;  
    while(nms--)
    {
        i=8000;  //������Ƶ����
        while(i--);    
    }
}
