#include "stm32f4xx.h" 
#include "stm32f4xx_rcc.h"// Device header
#include "stm32f4xx_gpio.h"
int main() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	
	GPIO_InitTypeDef GPIO_InitInstructure;
	GPIO_InitInstructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitInstructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitInstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitInstructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitInstructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIO_InitInstructure);
	GPIO_InitInstructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB,&GPIO_InitInstructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);		
	GPIO_SetBits(GPIOB,GPIO_Pin_13);

	while(1);
}  