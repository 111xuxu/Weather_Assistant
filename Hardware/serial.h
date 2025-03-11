#ifndef __serial_h
#define __serial_h


extern uint8_t TxPacket[];
extern uint8_t RxPacket[];
extern char Recieve_String[1900];
void MYUSART_Init();


void USART_SendByte(uint8_t Byte);
void USART_SendArray(uint8_t *Array,uint16_t Length);
void USART_SendString(char *string);
uint32_t Serial_Pow(uint32_t X,uint32_t Y);
void USART_SendNumber(uint32_t Number,uint8_t Length);
uint8_t GetRxData(void);
uint8_t GetRxFlag(void);
void USART1_IRQHandler(void);
void USART_SendPacket(void);

#endif
