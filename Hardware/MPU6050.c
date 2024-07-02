/*
 * @日期: 2024-06-06 21:27:10
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-06 22:57:55
 * @文件相对于项目的路径: \10-1ruanjianduxieMPU6050\Hardware\MPU6050.c
 * @描述:
 */
#include "stm32f10x.h"
#include "MyI2C.h"
#include "MPU6050_Reg.h"
#define MPU6050_ADDRESS 0x78
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_RecAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_RecAck();
	MyI2C_SendByte(Data);
	MyI2C_RecAck();
	MyI2C_Stop();
}
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_RecAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_RecAck();

	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
	MyI2C_RecAck();
	Data = MyI2C_RecByte();
	MyI2C_SendAck(1);
	MyI2C_Stop();
	return Data;
}
void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}
void MPU6050_GetData(int16_t* Accx, int16_t* Accy, int16_t* Accz, int16_t* Gyrox, int16_t* Gyroy, int16_t* Gyroz)
{
	uint8_t DataH, DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*Accx = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*Accy = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*Accz = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*Gyrox = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*Gyroy = (DataH << 8) | DataL;
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*Gyroz = (DataH << 8) | DataL;
}