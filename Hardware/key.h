/*
 * @日期: 2024-01-21 22:39:50
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-01-21 22:39:52
 * @文件相对于项目的路径: \GPIO输入\Hardware\key.h
 * @描述: 
 */
#ifndef __KEY_H
#define __KEY_H

void Key_Init(void);
uint8_t Key_GetNum(void);
void LED0_TURN(void);
void LED1_TURN(void);

#endif // __KEY_H