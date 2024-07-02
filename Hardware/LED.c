/*
 * @日期: 2024-01-21 18:32:00
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-01-21 23:43:14
 * @文件相对于项目的路径: \GPIO输入\Hardware\LED.c
 * @描述: LED驱动文件
 */
#include "stm32f10x.h"
/**
 * @brief 初始化LED
 * @return {*}
 */
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_0);
}
/**
 * @brief 开灯0
 * @return {*}
 */
void LED0_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

/**
 * @brief 关灯0
 * @return {*}
 */
void LED0_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
}
/**
 * @brief 开灯1
 * @return {*}
 */
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

/**
 * @brief 关灯1
 * @return {*}
 */
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);
}
/**
 * @brief LED0切换
 * @return {*}
 */
void LED0_TURN(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)==0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	}
}
/**
 * @brief LED1切换
 * @return {*}
 */
void LED1_TURN(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)==0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}
