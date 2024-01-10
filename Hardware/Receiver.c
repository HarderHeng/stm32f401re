#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_tim.h" 
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
void ICTIM2CH1_2_Init(void)//PA0--TIM2CH1   
{
//开启时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
//引脚复用
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);   
//GPIO初始化
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
//时基单元初始化  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//arr
    TIM_TimeBaseInitStructure.TIM_Prescaler = 16-1;//psc
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
 //输入捕获初始化
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0x0F;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM2,&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICFilter = 0x0F;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;
    TIM_ICInit(TIM2,&TIM_ICInitStructure);
//选择从模式触发源以及工作模式
    TIM_SelectInputTrigger(TIM2,TIM_TS_TI1FP1); 
    TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
//开启定时器  
    TIM_Cmd(TIM2,ENABLE);
} 

