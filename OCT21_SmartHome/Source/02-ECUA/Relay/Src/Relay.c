/*
 * Relay.c
 *
 * Created on: Oct , 2022
 * Author: Youssef Ali
 */ 

#include "Relay.h"

void	Relay_Init		(void)
{
	Dio_vidconfigChanel(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);
}

void	Relay_On			(void)
{
	Dio_vidwriteChanel(DIO_PORTA,DIO_PIN4,DIO_HIGH);

}

void	Relay_Off		    (void)
{
	Dio_vidwriteChanel(DIO_PORTA,DIO_PIN4,DIO_LOW);
}
