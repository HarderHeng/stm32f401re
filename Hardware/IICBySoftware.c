#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"// Device header
#include "stm32f4xx_gpio.h"// Device header
#include "Delay.h"
/**
 * @brief 初始化函数
 */
void IIC_Init(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitInstructure;
	GPIO_InitInstructure.GPIO_Mode = GPIO_Mode_OUT; //输出模式
	GPIO_InitInstructure.GPIO_OType = GPIO_OType_OD; //开漏输出可以不用切换输入输出模式
	GPIO_InitInstructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitInstructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉输入
	GPIO_InitInstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SetBits(GPIOA, GPIO_Pin_13 | GPIO_Pin_14);
	//初始化GPIOA的13和14口
}
/**
*@brief 向SCL写数值
*/
void SCL_W(int x) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_13, (BitAction)x);
	Delay_us(10);
}
/**
*@brief 向SDA写数值
*/
void SDA_W(int x) {
	GPIO_WriteBit(GPIOA, GPIO_Pin_14, (BitAction)x);
	Delay_us(10);
}
/**
*@brief 读取SDA
*/
uint8_t SDA_R(void) {
	uint8_t bit;
	bit = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_14);
	Delay_us(10);
	return bit;
}
/**
*@brief 产生起始条件
*/
void IIC_Start(void) {
	SDA_W(1); //将SDA在SCL拉高之前就拉高，防止产生终止条件
	SCL_W(1);
	SDA_W(0); //拉低SDA
	SCL_W(0); //拉低SCL
}
/**
*@brief 产生终止条件
*/
void IIC_Stop(void) {
	SDA_W(0); //确保SDA低电平
	SCL_W(1); //拉高SCL
	SDA_W(1); //在SCL高电平时拉高SDA
}
/**
*@brief 发送一个字节
*/
void IIC_SendByte(uint8_t byte) {
	for(int i = 0; i < 8; i++) {
		SDA_W(byte & (0x80>>i)); //发送一个字节的一位
		SCL_W(1);
		SCL_W(0); //先拉高SCL再拉低
	}
}
/**
*@brief 接收一个字节
*/
uint8_t IIC_ReceiveByte(void) {
	uint8_t byte = 0x00;
	SDA_W(1);
	for(int i = 7; i >=0 ; i--) {
		SCL_W(1);                 
		byte = byte | (SDA_R() << i);
		SCL_W(0);
	}
	return byte;
}
/**
*@brief 发送应答
*/
void IIC_SendACK(uint8_t byte) {
	SDA_W(byte); //发送一个应答位
	SCL_W(1); //拉高SCL让从机读取
	SCL_W(0); //拉低SCL进入下一个时序
}
/**
*@brief 接收应答
*/
uint8_t IIC_ReceiveACK(void) {
	uint8_t bit;
	SDA_W(1); //主机释放SDA
	SCL_W(1); //主机拉高SCL读取从机的应答
	bit = SDA_R();
	SCL_W(0);
	return bit;
}
