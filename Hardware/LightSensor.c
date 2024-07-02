/*
 * @日期: 2024-01-22 00:00:22
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-01-22 00:02:55
 * @文件相对于项目的路径: \3-5光敏蜂鸣器\Hardware\LightSensor.c
 * @描述: 
 */
#include "stm32f10x.h"
#include "Delay.h"
/**
 * @brief 光敏始化
 * @return {*}
 */
void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t LightSensor_Get(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}