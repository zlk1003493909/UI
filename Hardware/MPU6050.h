/*
 * @日期: 2024-06-06 21:27:34
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-06 22:59:15
 * @文件相对于项目的路径: \10-1ruanjianduxieMPU6050\Hardware\MPU6050.h
 * @描述:
 */
#ifndef __MPU6050_H
#define __MPU6050_H
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);
void MPU6050_Init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t* Accx, int16_t* Accy, int16_t* Accz, int16_t* Gyrox, int16_t* Gyroy, int16_t* Gyroz);
#endif // __MPU6050_H
