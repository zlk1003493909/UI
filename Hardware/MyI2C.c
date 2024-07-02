/*
 * @日期: 2024-06-08 12:24:20
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-08 12:24:22
 * @文件相对于项目的路径: \moban\Hardware\MyI2C.c
 * @描述: 
 */
/*
 * @日期: 2024-06-06 20:23:50
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-06 22:28:18
 * @文件相对于项目的路径: \10-1ruanjianduxieMPU6050\Hardware\MyI2C.c
 * @描述:
 */
#include "stm32f10x.h"
#include "Delay.h"
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
	Delay_us(10);
}
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
	Delay_us(10);
}
uint8_t MyI2C_R_SDA(void)
{
	uint8_t Bitvalue;
	Bitvalue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(10);
	return Bitvalue;
}
void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_10| GPIO_Pin_11);
}

// 起始条件
void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}
// 终止条件
void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}
// 发送一个字节
void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i ;
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}
// 接收一个字节
uint8_t MyI2C_RecByte(void)
{
	uint8_t Byte=0x00;
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		MyI2C_W_SDA(1);
		MyI2C_W_SCL(1);
		if (MyI2C_R_SDA() == 1)
		{
			Byte |= (0x80 >> i);
		}
		MyI2C_W_SCL(0);
	}
	return Byte;
}
// 发送应答
void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}
// 接收应答
uint8_t MyI2C_RecAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}
