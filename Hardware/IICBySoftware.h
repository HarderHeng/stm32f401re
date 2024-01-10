#ifndef __IICBYSOFTWARE_H
#define __IICBYSOFTWARE_H
void Init(void);
void Start(void);
void Stop(void);
void SendByte(uint8_t byte);
uint8_t ReceiveByte(void);
void SendACK(uint8_t byte);
uint8_t ReceiveACK(void);
#endif
