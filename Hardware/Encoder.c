/*
 * @日期: 2024-01-22 20:54:34
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-22 22:49:42
 * @文件相对于项目的路径: \ui\Hardware\Encoder.c
 * @描述:
 */
#include "stm32f10x.h"
#include "oled_ui.h"

int16_t Encoder_Count = 0;
void Encoder_Init(void)
{

	// 配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	// GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; // 下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0); // PB0
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1); // PB1

	// EXTI
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line    = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;  // 中断模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
	EXTI_Init(&EXTI_InitStruct);

	// NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中级优先级
	NVIC_InitTypeDef NVIC_IRQ_EXTI14;
	NVIC_IRQ_EXTI14.NVIC_IRQChannel                   = EXTI0_IRQn;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_IRQ_EXTI14);
	NVIC_IRQ_EXTI14.NVIC_IRQChannel                   = EXTI1_IRQn;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_IRQ_EXTI14.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_IRQ_EXTI14);
}

int16_t Encoder_Read(void)
{
	int16_t Temp;
	Temp          = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
		{
			Encoder_Count--;
			OLED_MsgQueSend(msg_up);
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			Encoder_Count++;
			OLED_MsgQueSend(msg_down);
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}