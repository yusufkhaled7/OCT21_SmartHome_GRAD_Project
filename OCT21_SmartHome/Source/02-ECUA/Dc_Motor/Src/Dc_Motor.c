/*
 * Dc_Motor.c
 *
 *  Created on: Sep, 2022
 *      Author: Yusuf Khaled
 */



#include "Dio.h"
#include "Dc_Motor.h"
#include "util/delay.h"

void Dc_Motor_vidInit(void)
{
	/*	Configure Motor Control Pins as Outputs	*/
	Dio_vidconfigChanel(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
	Dio_vidconfigChanel(DIO_PORTC,DIO_PIN4,DIO_OUTPUT);

	/*	Make Sure Motor is Stop	*/
	Dio_vidwriteChanel(DIO_PORTD,DIO_PIN4,DIO_LOW);
}
void Dc_Motor_vidStart(motor_dir_t dir)
{
	if (dir == DIR_CW)
	{
		/*	Set IN1 Pin	*/
		Dio_vidwriteChanel(DIO_PORTC,DIO_PIN3,DIO_HIGH);
		/*	Clear IN2 Pin	*/
		Dio_vidwriteChanel(DIO_PORTC,DIO_PIN4,DIO_LOW);
	}
	else
	{
		/*	Clear IN1 Pin	*/
		Dio_vidwriteChanel(DIO_PORTC,DIO_PIN3,DIO_LOW);
		/*	Set IN2 Pin	*/
		Dio_vidwriteChanel(DIO_PORTC,DIO_PIN4,DIO_HIGH);
	}

	/*	Set EN1 Pin	*/
	Dio_vidwriteChanel(DIO_PORTD,DIO_PIN4,DIO_HIGH);
}
void Dc_Motor_vidStop(void)
{
	/*	Clear EN1 Pin	*/
	Dio_vidwriteChanel(DIO_PORTD,DIO_PIN4,DIO_LOW);

	/*	Wait Till Motor Stop	*/
	_delay_ms(3000);
}
