#ifndef __IICBYSOFTWARE_H
#define __IICBYSOFTWARE_H
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(uint8_t byte);
uint8_t IIC_ReceiveByte(void);
void IIC_SendACK(uint8_t byte);
uint8_t IIC_ReceiveACK(void);
#endif
