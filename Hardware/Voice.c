#include "stm32f10x.h"                  // Device header
#include "delay.h"

extern uint8_t Tem_High;
extern uint8_t Tem_Low;

void Voice_Init(void)
	
{

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}

void Voice_SendData(uint8_t Data)
{
	int i;
GPIO_SetBits(GPIOA,GPIO_Pin_3);
	
	Delay_us(1000);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	Delay_us(4000);
	for(i=0;i<8;i++)
	{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	if((Data & 0x01)==1)
	{
	Delay_us(1500);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		Delay_us(500);
	
	}
	else
	{
	Delay_us(500);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		Delay_us(1500);
	
	
	}
	Data>>=1;
	}
	
	GPIO_SetBits(GPIOA,GPIO_Pin_3);

}

void Voice_High()
{

switch (Tem_High)
	{	
		case 15:Voice_SendData(0x0A);Voice_SendData(0x05);Voice_SendData(0x0b);break;
		case 16:Voice_SendData(0x0A);Voice_SendData(0x06);Voice_SendData(0x0b);break;
		case 17:Voice_SendData(0x0A);Voice_SendData(0x07);Voice_SendData(0x0b);break;
		case 18:Voice_SendData(0x0A);Voice_SendData(0x08);Voice_SendData(0x0b);break;
		case 19:Voice_SendData(0x0A);Voice_SendData(0x09);Voice_SendData(0x0b);break;
		case 20:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x00);Voice_SendData(0x0b);break;
		case 21:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x01);Voice_SendData(0x0b);break;
		case 22:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x02);Voice_SendData(0x0b);break;
		case 23:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x03);Voice_SendData(0x0b);break;
		case 24:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x04);Voice_SendData(0x0b);break;
		case 25:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x05);Voice_SendData(0x0b);break;
		case 26:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x06);Voice_SendData(0x0b);break;
		case 27:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x07);Voice_SendData(0x0b);break;
		case 28:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x08);Voice_SendData(0x0b);break;
		case 29:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x09);Voice_SendData(0x0b);break;
		case 30:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x00);Voice_SendData(0x0b);break;
		case 31:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x01);Voice_SendData(0x0b);break;
		case 32:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x02);Voice_SendData(0x0b);break;
		case 33:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x03);Voice_SendData(0x0b);break;
		case 34:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x04);Voice_SendData(0x0b);break;
		case 35:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x05);Voice_SendData(0x0b);break;
		case 36:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x06);Voice_SendData(0x0b);break;
		case 37:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x07);Voice_SendData(0x0b);break;
	
	}
}
	
	void Voice_Low()
{

switch (Tem_Low)
	{	
		case 15:Voice_SendData(0x0A);Voice_SendData(0x05);Voice_SendData(0x0b);break;
		case 16:Voice_SendData(0x0A);Voice_SendData(0x06);Voice_SendData(0x0b);break;
		case 17:Voice_SendData(0x0A);Voice_SendData(0x07);Voice_SendData(0x0b);break;
		case 18:Voice_SendData(0x0A);Voice_SendData(0x08);Voice_SendData(0x0b);break;
		case 19:Voice_SendData(0x0A);Voice_SendData(0x09);Voice_SendData(0x0b);break;
		case 20:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x00);Voice_SendData(0x0b);break;
		case 21:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x01);Voice_SendData(0x0b);break;
		case 22:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x02);Voice_SendData(0x0b);break;
		case 23:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x03);Voice_SendData(0x0b);break;
		case 24:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x04);Voice_SendData(0x0b);break;
		case 25:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x05);Voice_SendData(0x0b);break;
		case 26:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x06);Voice_SendData(0x0b);break;
		case 27:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x07);Voice_SendData(0x0b);break;
		case 28:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x08);Voice_SendData(0x0b);break;
		case 29:Voice_SendData(0x0A);Voice_SendData(0x01);Voice_SendData(0x09);Voice_SendData(0x0b);break;
		case 30:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x00);Voice_SendData(0x0b);break;
		case 31:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x01);Voice_SendData(0x0b);break;
		case 32:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x02);Voice_SendData(0x0b);break;
		case 33:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x03);Voice_SendData(0x0b);break;
		case 34:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x04);Voice_SendData(0x0b);break;
		case 35:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x05);Voice_SendData(0x0b);break;
		case 36:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x06);Voice_SendData(0x0b);break;
		case 37:Voice_SendData(0x0A);Voice_SendData(0x02);Voice_SendData(0x07);Voice_SendData(0x0b);break;
	
	}


}

void Voice_rain()
	
{
	Voice_SendData(0x0A);
	Voice_SendData(0x04);
	Voice_SendData(0x0b);


}


void Voice_sun()
{
Voice_SendData(0x0A);
	Voice_SendData(0x03);
	Voice_SendData(0x0b);

}