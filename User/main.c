#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h"// Device header
#include "stm32f4xx_gpio.h"
#include "misc.h"
#include "stm32f4xx_usart.h"
#include "Timer.h"
#include "Receiver.h"
#include "USART.h"
#include "PWM.h"
#include "Led.h"
int main() {
	Serial_Init();
	
	Led_Init();
	USART_SendData(USART1, 0x41);
	while(1){
		
	};
}  

