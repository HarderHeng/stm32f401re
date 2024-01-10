#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_tim.h" 
#include "stm32f4xx_rcc.h"
#include "misc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
void PWM_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	TIM_InternalClockConfig(TIM1); //开启TIM1的内部时钟
	TIM_TimeBaseInitTypeDef TIM_InitBaseInitStructure; //时基单元初始化结构体
	TIM_InitBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; //滤波器采样分频
	TIM_InitBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //计数方式向上计数
	TIM_InitBaseInitStructure.TIM_Period=10000-1; //自动重装器的值
	TIM_InitBaseInitStructure.TIM_Prescaler=7200-1; //分频系数
	TIM_InitBaseInitStructure.TIM_RepetitionCounter=0; //输出分频
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure; //GPIO初始化结构体
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //复用模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP; //推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8; //
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL; //没有上拉下拉
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure; //创建OC输出结构体
	TIM_OCStructInit(&TIM_OCInitStructure); //结构体自动赋初始值的函数
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; //PWM模式1
	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_High; //REF的极性翻转，高电平就是不翻转
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //输出状态开启
	TIM_OCInitStructure.TIM_Pulse=5000-1; //指定CCR的值
	TIM_OC1Init(TIM1,&TIM_OCInitStructure); //从OC1通道输出PWM信号
	
	TIM_Cmd(TIM1,ENABLE); //开启TIM
}
void PWM_SetCompare1(uint16_t compare){
	
	TIM_SetCompare1(TIM2,compare);
}