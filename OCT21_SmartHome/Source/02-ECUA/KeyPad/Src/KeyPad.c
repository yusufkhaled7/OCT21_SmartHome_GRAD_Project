/*
 * KeyPad.c
 *
 *  Created on: Oct , 2022
 *      Author: Mido Ayman
 */



#include "KeyPad.h"




void Keypad_vidinit(void)
{
	Dio_vidconfigChanel(DIO_PORTC,DIO_PIN3,OUTPUT);
	Dio_vidconfigChanel(DIO_PORTC,DIO_PIN4,OUTPUT);
	Dio_vidconfigChanel(DIO_PORTC,DIO_PIN5,OUTPUT);
	Dio_vidconfigChanel(DIO_PORTC,DIO_PIN6,OUTPUT);

	Dio_vidconfigChanel(DIO_PORTB,DIO_PIN4,INPUT);
	Dio_vidconfigChanel(DIO_PORTB,DIO_PIN5,INPUT);
	Dio_vidconfigChanel(DIO_PORTB,DIO_PIN6,INPUT);
	Dio_vidconfigChanel(DIO_PORTB,DIO_PIN7,INPUT);



	// to activate internal pull up res

	Dio_vidPullUpEn(DIO_PORTB,DIO_PIN4);
	Dio_vidPullUpEn(DIO_PORTB,DIO_PIN5);
	Dio_vidPullUpEn(DIO_PORTB,DIO_PIN6);
	Dio_vidPullUpEn(DIO_PORTB,DIO_PIN7);


	Dio_vidSetPinValue(KEYPAD_R0_PIN,HIGH);
	Dio_vidSetPinValue(KEYPAD_R1_PIN,HIGH);
	Dio_vidSetPinValue(KEYPAD_R2_PIN,HIGH);
	Dio_vidSetPinValue(KEYPAD_R3_PIN,HIGH);
}
u8   Keypad_getChar(void)
{
	u8 Local_U8_Arr [4][4] = { { '1' , '2' , '3' , 'A' },
			                   { '4' , '5' , '6' , 'B' },
		                       { '7' , '8' , '9' , 'C' },
			                   { '*' , '0' , '#' , 'D' }};
	u8 Local_U8_Reading = 0;
	u8 Local_U8_Row = 0;
	u8 Local_U8_Col = 0;
	for(Local_U8_Row=KEYPAD_R0_PIN;Local_U8_Row<=KEYPAD_R3_PIN;Local_U8_Row++)
	{
		Dio_vidSetPinValue(Local_U8_Row,LOW);
		for(Local_U8_Col=KEYPAD_C0_PIN;Local_U8_Col<=KEYPAD_C3_PIN;Local_U8_Col++)
		{
			if(Dio_GetPinValue(Local_U8_Col) == KEYPAD_PRESSED)
			{
				_delay_ms(KEYPAD_DEBOUNCING_TIME);
				if(Dio_GetPinValue(Local_U8_Col) == KEYPAD_PRESSED)
				{
					while(Dio_GetPinValue(Local_U8_Col) == KEYPAD_PRESSED);
					Local_U8_Reading = Local_U8_Arr[Local_U8_Row-KEYPAD_R0_PIN][Local_U8_Col-KEYPAD_C0_PIN];
					break;
				}
			}
		}
		Dio_vidSetPinValue(Local_U8_Row,HIGH);
	}
	return Local_U8_Reading;
}











