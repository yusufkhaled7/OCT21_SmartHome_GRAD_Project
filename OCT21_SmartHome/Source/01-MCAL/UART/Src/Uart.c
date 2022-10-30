/*
 * Uart.c
 * Created: Oct , 2022
 *  Author: Youssef Galal
 */

#include "Uart_Reg.h"
#include "Uart.h"
#include "Std_Types.h"
#include "Bit_Math.h"

void USART_Init(u32 baud)
{
	/*	Calculate UBRR Value	*/
	u32 loc_UBBR_val = ((F_OSC/(16*baud))-1);
	/* Set baud rate */
	UART_UBRRH_REG = loc_UBBR_val>>8;
	UART_UBRRL_REG = loc_UBBR_val;
	/* Enable receiver and transmitter */
	UART_UCSRB_REG = (1<<UART_RXEN_BIT)|(1<<UART_TXEN_BIT);
	/* Set frame format: 8data, 2stop bit */
	UART_UCSRC_REG = (1<<UART_URSEL_BIT)|(1<<UART_USBS_BIT)|(3<<UART_UCSZ0_BIT);
}

void USART_TransmitChr(u8 data)
{
	/* Wait for empty transmit buffer */
	while (CHECK_BIT(UART_UCSRA_REG,UART_UDRE_BIT) == 0)
	{
		;
	}
		/* Put data into buffer, sends the data */
	UART_UDR_REG = data;
}

u8 USART_Receive_Blocking(void)
{
	/* Wait for data to be received */
	while (CHECK_BIT(UART_UCSRA_REG,UART_RXC_BIT) == 0)
	{
		;
	}
	/* Get and return received data from buffer */
	return UART_UDR_REG;
}
u8 USART_Receive_NonBlocking(void)
{
	/* Wait for data to be received */
	if (CHECK_BIT(UART_UCSRA_REG,UART_RXC_BIT) == 1)
	{
		/* Get and return received data from buffer */
		return UART_UDR_REG;
	}
	else
	{
		return 0;
	}

}
void USART_TransmitStr(u8 *str)
{
	while (*str != '\0')
	{
		USART_TransmitChr(*str);
		str++;
	}
}
void USART_Receive_InterruptEnable(void)
{
	SET_BIT(UART_UCSRB_REG,UART_RXCIE_BIT);
}
