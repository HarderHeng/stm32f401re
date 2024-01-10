#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h"// Device header
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "stm32f4xx_usart.h"
#include "Timer.h"
#include "Receiver.h"
#include "USART.h"
#include "PWM.h"
static __IO uint32_t TimingDelay;

void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}


void delay_us(uint32_t time)
{    
   /*int i=0;  
   while(time--)
   {
      i=10;  //自己定义
      while(i--) ;    
   }*/
	 uint32_t i , j ; 
  for(i = 0 ; i < time ; i++)
  {
    for(j = 0 ; j < 0xfff ; j++)
    { }
 }
}


int main() {
	Serial_Init();
	
	PWM_Init();
	while(1){
		
	};
}  

