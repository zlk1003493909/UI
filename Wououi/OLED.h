/*
 * @日期: 2024-06-21 20:31:01
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-22 21:46:20
 * @文件相对于项目的路径: \ui\Wououi\OLED.h
 * @描述: 
 */
#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"

void OLED_Init(void);
void OLED_Clear(void);
void OLED_SendBuff(uint8_t buff[8][128]);

#endif
