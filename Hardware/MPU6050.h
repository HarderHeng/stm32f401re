#ifndef __MPU6050_H
#define __MPU6050_H
void MPU_Init(void);
void MPU_GetArgulaData(uint8_t *array);
void MPU_GetAccelorationData(uint8_t *array);
#endif