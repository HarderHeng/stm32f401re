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
	Serial_SendByte(0x41);
	Led_Init();
	while(1){
		
	};
}  

