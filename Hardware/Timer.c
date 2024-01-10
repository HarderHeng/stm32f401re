#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_tim.h" 
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
void Timer_Init(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC ,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_High_Speed;
    GPIO_Init(GPIOC , &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 2000 - 1;//ARR F=50hz
    TIM_TimeBaseInitStruct.TIM_Prescaler = 160 - 1;//PSC
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0;//用以设置CCR
    TIM_OC1Init(TIM3, &TIM_OCInitStruct);
    TIM_OC2Init(TIM3, &TIM_OCInitStruct);
    TIM_OC3Init(TIM3, &TIM_OCInitStruct);
    TIM_OC4Init(TIM3, &TIM_OCInitStruct);

	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3,ENABLE);

	TIM_InternalClockConfig(TIM3);
	TIM_Cmd(TIM3, ENABLE);
}