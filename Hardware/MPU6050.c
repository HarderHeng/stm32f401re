#include "stm32f4xx.h"                  // Device header
#include "IICBySoftware.h"
#define MPU6050_Address 0xD0 //从机8位地址

#define SampleRateDivider 0x19 //采样频率，值为0x07
#define ConfigRegAddress 0x1A //0x06
#define GYROConfigRegAddress 0x1B //0x18
#define AccelConfigRegAddress 0x1C //0x01

#define ACCEL_XOUT_H 0x3B 
#define ACCEL_XOUT_L 0x3C 
#define ACCEL_YOUT_H 0x3D 
#define ACCEL_YOUT_L 0x3E 
#define ACCEL_ZOUT_H 0x3F 
#define ACCEL_ZOUT_L 0x40 

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44 
#define GYRO_YOUT_H 0x45 
#define GYRO_YOUT_L 0x46 
#define GYRO_ZOUT_H 0x47 
#define GYRO_ZOUT_L 0x48 

#define PWR_MGMT_1 0x6B //0x00

void MPU_WriteRegAdress(uint8_t address, uint8_t data){
	IIC_Start();
	IIC_SendByte(MPU6050_Address);
	IIC_ReceiveACK();
	IIC_SendByte(address);
	IIC_ReceiveACK();
	IIC_SendByte(data);
	IIC_ReceiveACK();
	IIC_Stop();
}
uint8_t MPU_ReadRegAdress(uint8_t address){
	uint8_t byte;
	IIC_Start();
	IIC_SendByte(MPU6050_Address);
	IIC_ReceiveACK();
	IIC_SendByte(address);
	IIC_Start();
	IIC_SendByte(MPU6050_Address|0x01);
	IIC_ReceiveACK();
	byte=IIC_ReceiveByte();
	IIC_SendACK(1);
}
void MPU_GetAccelorationData(uint8_t *array){
	uint8_t NowAddress = ACCEL_XOUT_H;
	for(int i = 0;i<=2;i++){
		array[i]=((MPU_ReadRegAdress(NowAddress)<<8)|MPU_ReadRegAdress(NowAddress+1));
		NowAddress+=2;
	}
}
void MPU_GetArgulaData(uint8_t *array){
	uint8_t NowAddress=GYRO_XOUT_H;
	for(int i = 0;i<=2;i++){
		array[i]=((MPU_ReadRegAdress(NowAddress)<<8)|MPU_ReadRegAdress(NowAddress+1));
		NowAddress+=2;
	}
}
void MPU_Init(void){
	IIC_Init();
	MPU_WriteRegAdress(PWR_MGMT_1,0x00);
	MPU_WriteRegAdress(SampleRateDivider,0x07);
	MPU_WriteRegAdress(ConfigRegAddress,0x06);
	MPU_WriteRegAdress(GYROConfigRegAddress,0x18);
	MPU_WriteRegAdress(AccelConfigRegAddress,0x01);
}