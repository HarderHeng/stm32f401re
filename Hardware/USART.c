#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"
//使用USART1外设，对应板子上的PB6（TX）和PB7（RX）
uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //初始化USART1的时钟
	USART_InitTypeDef USART_InitInstructure; //初始化USART外设（类似于初始化GPIO端口）
	USART_InitInstructure.USART_BaudRate = 9600;//波特率
	USART_InitInstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制
	USART_InitInstructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //USART模式，既接受也发送
	USART_InitInstructure.USART_Parity = USART_Parity_No; //校验位
	USART_InitInstructure.USART_StopBits = USART_StopBits_1; //停止位一位
	USART_InitInstructure.USART_WordLength = USART_WordLength_8b; //每一句长8bit
	USART_Init(USART1, &USART_InitInstructure);
	
	GPIO_PinAFConfig(GPIOB,6,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB,7,GPIO_AF_USART1);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //初始化GPIOA的时钟
	GPIO_InitTypeDef GPIO_InitInstructure;
	GPIO_InitInstructure.GPIO_Mode = GPIO_Mode_AF; //GPIO复用模式才能被USART外设所调用
	GPIO_InitInstructure.GPIO_OType = GPIO_OType_PP; //USART要用推挽
	GPIO_InitInstructure.GPIO_Pin = GPIO_Pin_7; //初始化两个口，现在两个口同时具有输入和输出的能力，实际上只需要TX输出，RX输入 
	GPIO_InitInstructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉输入
	GPIO_InitInstructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitInstructure);
	
	GPIO_InitInstructure.GPIO_Mode = GPIO_Mode_AF; //GPIO复用模式才能被USART外设所调用
	GPIO_InitInstructure.GPIO_OType = GPIO_OType_PP; //USART要用推挽
	GPIO_InitInstructure.GPIO_Pin = GPIO_Pin_6; //初始化两个口，现在两个口同时具有输入和输出的能力，实际上只需要TX输出，RX输入 
	GPIO_InitInstructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉输入
	GPIO_InitInstructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitInstructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启RXNE标志位的中断,当接收寄存器不是空的时候触发中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitInstructure;
	NVIC_InitInstructure.NVIC_IRQChannel = USART1_IRQn; //NVIC中断通道USART1
	NVIC_InitInstructure.NVIC_IRQChannelCmd = ENABLE; //开启NVIC中断
	NVIC_InitInstructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级
	NVIC_InitInstructure.NVIC_IRQChannelSubPriority = 1; //响应优先级
	NVIC_Init(&NVIC_InitInstructure);
	
	GPIO_PinAFConfig(GPIOB,6,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB,7,GPIO_AF_USART1);
	
	USART_Cmd(USART1, ENABLE);
}
void Serial_SendByte(uint8_t byte) {
	USART_SendData(USART1, byte);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}
uint8_t Serial_ReceiveByte(void){
	Serial_RxFlag = 0;
	return Serial_RxData;
}
void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}
uint8_t GetRxFlag(void) {
	if(Serial_RxFlag==1){
		Serial_RxFlag=0;
		return 1;
	}
	else{
		Serial_RxFlag=1;
	}
	return 0;
}
void USART_IRQHandler(void) {
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET) {
		Serial_RxData=USART_ReceiveData(USART1);
		Serial_RxFlag=1;
	}
		
}