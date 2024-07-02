/*
 * @日期: 2024-01-21 23:52:38
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-01-21 23:55:56
 * @文件相对于项目的路径: \3-5光敏蜂鸣器\Hardware\Buzzer.c
 * @描述: 
 */
#include "stm32f10x.h"
/**
 * @brief 初始化蜂鸣器
 * @return {*}
 */
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/**
 * @brief 蜂鸣器打开
 * @return {*}
 */
void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

/**
 * @brief 蜂鸣器关闭
 * @return {*}
 */
void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

