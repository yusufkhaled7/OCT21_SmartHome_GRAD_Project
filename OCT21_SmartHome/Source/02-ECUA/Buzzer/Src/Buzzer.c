/*
 * Button.c
 *
 *  Created on: Sep , 2022
 *      Author: Mazen Mokbel
 */
#include "Dio.h"

void Buzzer_vidinit(void)
{
	Dio_vidconfigChanel(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);
}
void Buzzer_vidbuzzerOn(void)
{
	Dio_vidwriteChanel(DIO_PORTA, DIO_PIN3, DIO_HIGH);
}
void Buzzer_vidbuzzerOff(void)
{
	Dio_vidwriteChanel(DIO_PORTA, DIO_PIN3, DIO_LOW);
}
