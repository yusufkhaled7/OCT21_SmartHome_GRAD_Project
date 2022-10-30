/*
 * Hc05.c
 *
 * Created: Oct , 2022
 *  Author: Malek Elsaka
 */ 
#include "Hc05.h"


void Hc05_Init(void)
{
    USART_Init(9600);
}
void Hc05_Send(u8 Local_u8_Data)
{
   USART_TransmitChr(Local_u8_Data);
}

void Hc05_SendString(u8* Local_u8_PtrToString)
{
	u8 Local_u8_Counter = 0;
	u8 Local_u8_Data = 0;
	while (Local_u8_PtrToString[Local_u8_Counter] !='\0')
	{
		Local_u8_Data=Local_u8_PtrToString[Local_u8_Counter];
		Hc05_Send(Local_u8_Data);
		_delay_ms(50);
		Local_u8_Counter++;
	}
}
u8 Hc05_Rec(void)
{
	u8 Local_u8_Data = 0;
	Local_u8_Data = USART_Receive_Blocking();
	return Local_u8_Data;
}
