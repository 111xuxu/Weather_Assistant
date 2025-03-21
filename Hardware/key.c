#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"

void Key_Init()
	
{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		

}

uint8_t Key_GetNum(void)
	{
	int8_t KeyNum=0;
		
	if(	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0)
	{
	Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
		Delay_ms(20);
		KeyNum=1;
		
	
	}
	if(	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
	Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==0);
		Delay_ms(20);
		KeyNum=2;

	}
	if(	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
	Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0);
		Delay_ms(20);
		KeyNum=3;

	}


		
		return KeyNum;
	
	
	}
	
	