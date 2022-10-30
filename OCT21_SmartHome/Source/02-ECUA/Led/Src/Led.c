/*
 * Led.c
 *  Created on: Sep , 2022
 *  Author: Youssef Galal
 */

#include "Dio.h"
#include "Led.h"

void Led_vidinit(void)
{
	Dio_vidconfigChanel(DIO_PORTC, DIO_PIN2,DIO_OUTPUT);
	Dio_vidconfigChanel(DIO_PORTC, DIO_PIN7,DIO_OUTPUT);
	Dio_vidconfigChanel(DIO_PORTD, DIO_PIN3,DIO_OUTPUT);
}

void Led_vidledOn(led_ledId_t ledId)
{
	switch (ledId)
	{
	case LED0:
		Dio_vidwriteChanel(DIO_PORTC, DIO_PIN2, DIO_HIGH);
		break;

	case LED1:
		Dio_vidwriteChanel(DIO_PORTC, DIO_PIN7, DIO_HIGH);
		break;

	case LED2:
		Dio_vidwriteChanel(DIO_PORTD, DIO_PIN3, DIO_HIGH);
		break;
	}
}

void Led_vidledOff(led_ledId_t ledId)
{
	switch (ledId)
	{
	case LED0:
		Dio_vidwriteChanel(DIO_PORTC, DIO_PIN2, DIO_LOW);
		break;

	case LED1:
		Dio_vidwriteChanel(DIO_PORTC, DIO_PIN7, DIO_LOW);
		break;

	case LED2:
		Dio_vidwriteChanel(DIO_PORTD, DIO_PIN3, DIO_LOW);
		break;
	}
}
void Led_vidledToggle(led_ledId_t ledId)
{
	switch (ledId)
	{
	case LED0:
		Dio_vidflipChanel(DIO_PORTC, DIO_PIN2);
		break;

	case LED1:
		Dio_vidflipChanel(DIO_PORTC, DIO_PIN7);
		break;

	case LED2:
		Dio_vidflipChanel(DIO_PORTD, DIO_PIN3);
		break;
	}
}
