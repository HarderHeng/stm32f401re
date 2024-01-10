#include "stm32f4xx.h"                  // Device header
#define HMC_5883LAddres 0x3C //MPU6050的八位地址
#define ConfigRegAddress_A 0x00 //向配置寄存器A中写入的值为01110000
#define ConfigRegAddress_B 0x01 //向配置寄存器B中写入的值为00100000
#define ModeRegAddress 0x02 //向模式寄存器中写入的值为10000000