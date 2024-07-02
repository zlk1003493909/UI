/*
 * @日期: 2024-01-22 19:32:15
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-01-22 20:05:51
 * @文件相对于项目的路径: \5-1对射式红外\Hardware\CountSensor.c
 * @描述:
 */
#include "stm32f10x.h"
/**
 * @brief 初始化对射式红外中断
 * @return {*}
 */
void CountSensor_Init(void)
{

	// 配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; // 上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14); // PB14

	// EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line    = EXTI_Line14;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;  // 中断模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
	EXTI_Init(&EXTI_InitStruct);

	// NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中级优先级
	NVIC_InitTypeDef NVIC_IRQ_EXTI14;
	NVIC_IRQ_EXTI14.NVIC_IRQChannel                   = EXTI15_10_IRQn;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_IRQ_EXTI14);
}
/**
 * @brief 中断处理函数
 * @return {*}
 */
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line14)==SET)
    {
		EXTI_ClearITPendingBit(EXTI_Line14);// 清除中断标志位
	}
}
