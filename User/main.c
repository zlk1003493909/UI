/*
 * @日期: 2024-06-08 12:24:02
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-22 23:04:46
 * @文件相对于项目的路径: \ui\User\main.c
 * @描述: 
 */

/*
 * @日期: 2024-01-21 00:36:28
 * @最后作者: 郑力奎
 * @最后编辑时间: 2024-06-08 00:21:18
 * @文件相对于项目的路径: \10-1ruanjianduxieMPU6050\User\main.c
 * @描述:
 */
#include "Delay.h"
#include "LED.h"
#include "key.h"
#include "Buzzer.h"
#include "OLED.h"
#include "LightSensor.h"
#include "CountSensor.h"
#include "Encoder.h"
#include "stm32f10x.h" // Device header
#include "TestUI.h"
uint8_t encode_num=0;
uint8_t Keynum=0;
uint8_t last_encode_num=0;
int main(void)
{
	TestUI_Init();
	Encoder_Init();
	Key_Init();
	while (1)
	{
		Keynum = Key_GetNum();
		if(Keynum==1)
		{
			OLED_MsgQueSend(msg_click);
		}
		TestUI_Proc();
	}
}
