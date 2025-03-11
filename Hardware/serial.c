#include "stm32f10x.h"                  // Device header
#include "OLED.h"

uint8_t RxFlag;//接收标志位
uint8_t TxPacket[4];//输出数据缓存区
uint8_t RxPacket[4];//输入数据缓存区
extern uint16_t p;
extern int state;
extern char Recieve_String[1900];
extern uint32_t pRxstate;
void MYUSART_Init()
{	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate =115200 ;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode =USART_Mode_Tx|USART_Mode_Rx ;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_StopBits =USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b ;
	
	USART_Init(USART1,&USART_InitStructure);

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART1,ENABLE);
}

void USART_SendByte(uint8_t Byte)
{
USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

}


void USART_SendArray(uint8_t *Array,uint16_t Length)

{
	uint16_t i;
for(i=0;i<Length;i++)
	{USART_SendByte(Array[i]);}


}

void USART_SendString(char *string)
	
{
uint32_t i;
	for(i=0;string[i]!=0;i++)
	{USART_SendByte(string[i]);}



}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{

uint32_t Result=1;
	while(Y--)
	{
	Result *=X;
	}
return Result;
}

void USART_SendNumber(uint32_t Number,uint8_t Length)
{
uint16_t i;
for(i=0;i<Length;i++)
	{
	USART_SendByte(Number/Serial_Pow(10,Length-i-1)%10 +'0');
	
	}


}


uint8_t GetRxFlag(void)
{
if (RxFlag==1)
	{
		RxFlag=0;
		return 1;
	}
	return 0;

}

void USART1_IRQHandler(void)
{
	static uint8_t Rxstate=0;
	
if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
		{	uint8_t Rxdata = USART_ReceiveData(USART1);
			if(state==1)
			{
		
		if(Rxstate==0)
		{	
			 if(Rxdata== '[')			
			{
				Rxstate=1;
				pRxstate=0;			
			}		
		}	
		else if(Rxstate==1)
		{
			if(Rxdata==']')
			{
				Rxstate=2;
			}
			else 
			{
				Recieve_String[pRxstate]=Rxdata;
			pRxstate++;		
			}		
		}
		else if(Rxstate==2)		
		{
			if(Rxdata=='}')
			{
				
				Rxstate=0;
				Recieve_String[pRxstate]='\0';
				RxFlag=1;
			}	
		}
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
			else if(state==0)
				
			{
		
		
		 if(Rxstate==0)
		{

			if(Rxdata=='\r')
			{
				Rxstate=1;
			}
			else 
			{
				Recieve_String[pRxstate]=Rxdata;
			pRxstate++;
			}
		}
		else if(Rxstate==1)
		{
			if(Rxdata=='\n')
			{
				Rxstate=0;
				Recieve_String[pRxstate]='\0';
				p=pRxstate;
				RxFlag=1;
			}	
		}
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
			}
		}
}
void USART_SendPacket(void)
{
USART_SendByte(0xFF);
	USART_SendArray(TxPacket,4);
	USART_SendByte(0xFE);
}
