/*
 * @日期: 2024-06-06 20:24:02
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-06 22:00:12
 * @文件相对于项目的路径: \10-1ruanjianduxieMPU6050\Hardware\MyI2C.h
 * @描述:
 */
#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_RecByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_RecAck(void);
#endif // __MYI2C_H
