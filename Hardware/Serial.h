/*
 * @日期: 2024-03-17 22:13:12
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-03-23 15:43:56
 * @文件相对于项目的路径: \9-3chuankoushouifahex\Hardware\Serial.h
 * @描述:
 */
#ifndef __SERIAL_H
#define __SERIAL_H
#include "stdio.h"
extern uint8_t Serial_TxPacket[4];//发送缓冲
extern uint8_t Serial_RxPacket[4]; // 接收缓冲


void Serial_init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t* Array, uint16_t Length);
void Serial_SendString(char* String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char* format, ...);
uint8_t Serial_SendPacket(void);

uint8_t Serial_GetRxFlag(void);

#endif // __SERIAL_H