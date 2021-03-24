#include "led.h"
#include "stm32f10x.h"


void light_led_init();
void light_led_x(int index);


void light_led(int index)
{
    RCC->APB2ENR |= 1<<4;
    int i = 0;
    light_led_init();
    if(index == 0)
    {
        for(i=1;i<9;i++)
            light_led_x(i);
    }
    else
    {
        light_led_x(index);
    }
}

void light_led_init()
{
   // GPIOC->CRL = GPIO_CRL_MODE | GPIO_CRL_CNF;
}

void light_led_x(int index)
{
    if(index < 1 || index > 8)
        return ;
    GPIOC->CRL = GPIOC->CRL&(~(0x0000000F << (index-1)*4));
    GPIOC->CRL = GPIOC->CRL| (GPIO_CRL_MODE0 << (index-1)*4);
  //  GPIO->CRL = GPIOC->CRL| (GPIO_CRL_CNF0 << index*4);
    GPIOC->BSRR = (GPIO_BSRR_BR0 << (index - 1)); 
    return ;
}

