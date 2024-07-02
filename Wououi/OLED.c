/*
 * @日期: 2024-06-22 20:19:43
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-22 21:45:45
 * @文件相对于项目的路径: \ui\Wououi\OLED.c
 * @描述:
 */
/*
 * @日期: 2024-01-22 00:20:57
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-21 21:54:39
 * @文件相对于项目的路径: \ui\Wououi\OLED.c
 * @描述:
 */
#include "OLED.h"
#include "OLED_Font.h"
#define OLED_I2C_SCL_PORT GPIOB
#define OLED_I2C_SCL_PIN GPIO_Pin_6
#define OLED_I2C_SDA_PORT GPIOB
#define OLED_I2C_SDA_PIN GPIO_Pin_7

void OLED_I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 使能与 I2C 有关的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	/* I2C_SCL、I2C_SDA*/
	GPIO_InitStructure.GPIO_Pin   = OLED_I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD; // 开漏输出
	GPIO_Init(OLED_I2C_SCL_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = OLED_I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD; // 开漏输出
	GPIO_Init(OLED_I2C_SDA_PORT, &GPIO_InitStructure);

	I2C_InitTypeDef I2C_InitStructure;
	/* I2C 配置 */
	I2C_InitStructure.I2C_Mode                = I2C_Mode_I2C;
	I2C_InitStructure.I2C_ClockSpeed          = 400000;
	I2C_InitStructure.I2C_DutyCycle           = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1         = 0x30;
	I2C_InitStructure.I2C_Ack                 = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; /* I2C的寻址模式 */
	I2C_Init(I2C1, &I2C_InitStructure);
	I2C_Cmd(I2C1, ENABLE);
}

void I2C1_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout;
	Timeout = 10000;                                   // 给定超时计数时间
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS) // 循环等待指定事件
	{
		Timeout--;        // 等待时，计数值自减
		if (Timeout == 0) // 自减到0后，等待超时
		{
			/*超时的错误处理代码，可以添加到此处*/
			break; // 跳出等待，不等了
		}
	}
}

/**
 * @brief  OLED写命令
 * @param  Command 要写入的命令
 * @retval 无
 */
void OLED_WriteCommand(uint8_t Command)
{
	// while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

	I2C_Send7bitAddress(I2C1, 0x78, I2C_Direction_Transmitter);       // 硬件I2C发送从机地址，方向为发送
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV6

	I2C_SendData(I2C1, 0x00);                                 // 硬件I2C发送写命令
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8

	I2C_SendData(I2C1, Command);                             // 硬件I2C发送命令
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED); // 等待EV8_2

	I2C_GenerateSTOP(I2C1, ENABLE);
}

/**
 * @brief  OLED写数据
 * @param  Data 要写入的数据
 * @retval 无
 */
void OLED_WriteData(uint8_t Data)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

	I2C_Send7bitAddress(I2C1, 0x78, I2C_Direction_Transmitter);       // 硬件I2C发送从机地址，方向为发送
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV6

	I2C_SendData(I2C1, 0x40);                                 // 硬件I2C发送写命令
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8

	I2C_SendData(I2C1, Data);                                // 硬件I2C发送命令
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED); // 等待EV8_2

	I2C_GenerateSTOP(I2C1, ENABLE);
}

/**
 * @brief  OLED设置光标位置
 * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
 * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
 * @retval 无
 */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);                 // 设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4)); // 设置X位置高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));        // 设置X位置低4位
}

/**
 * @brief  OLED清屏
 * @param  无
 * @retval 无
 */
void OLED_Clear(void)
{
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for (i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}


/**
 * @brief  OLED初始化
 * @param  无
 * @retval 无
 */
void OLED_Init(void)
{
	uint32_t i, j;

	for (i = 0; i < 1000; i++) // 上电延时
	{
		for (j = 0; j < 1000; j++)
			;
	}

	OLED_I2C_Init(); // 端口初始化

	OLED_WriteCommand(0xAE); // 关闭显示

	OLED_WriteCommand(0xD5); // 设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);

	OLED_WriteCommand(0xA8); // 设置多路复用率
	OLED_WriteCommand(0x3F);

	OLED_WriteCommand(0xD3); // 设置显示偏移
	OLED_WriteCommand(0x00);

	OLED_WriteCommand(0x40); // 设置显示开始行

	OLED_WriteCommand(0xA1); // 设置左右方向，0xA1正常 0xA0左右反置

	OLED_WriteCommand(0xC8); // 设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA); // 设置COM引脚硬件配置
	OLED_WriteCommand(0x12);

	OLED_WriteCommand(0x81); // 设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9); // 设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB); // 设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4); // 设置整个显示打开/关闭

	OLED_WriteCommand(0xA6); // 设置正常/倒转显示

	OLED_WriteCommand(0x8D); // 设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF); // 开启显示

	OLED_Clear(); // OLED清屏
}
static void OLED_WriteByteArrayData(uint8_t* data_array, uint16_t len)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT); // 等待EV5

	I2C_Send7bitAddress(I2C1, 0x78, I2C_Direction_Transmitter);       // 硬件I2C发送从机地址，方向为发送
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED); // 等待EV6

	I2C_SendData(I2C1, 0x40);                                 // 硬件I2C发送写命令
	I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8

	for (uint8_t i = 0; i < len; i++)
	{
		I2C_SendData(I2C1, data_array[i]);                                 // 硬件I2C发送写命令
		I2C1_WaitEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING); // 等待EV8
	}
	I2C_GenerateSTOP(I2C1, ENABLE);

}

void OLED_SendBuff(uint8_t buff[8][128])
{
	for (uint8_t i = 0; i < 8; i++)
	{
		OLED_WriteCommand(0xb0 + i);           // 设置页地址（0~7）(b0-b7)
		OLED_WriteCommand(0x00);               // 设置显示位置—列低地址
		OLED_WriteCommand(0x10);               // 设置显示位置—列高地址
		OLED_WriteByteArrayData(buff[i], 128); // 写一页128个字符
	} // 更新显示
}
