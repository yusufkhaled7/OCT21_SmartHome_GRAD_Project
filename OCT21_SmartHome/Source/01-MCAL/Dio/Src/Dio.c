/*
 * Dio.c
 *
 *  Created on: Aug , 2022
 *      Author: Mido Ayman
 */
#include "Dio.h"
#include "Bit_Math.h"
#include "Std_Types.h"

void Dio_vidconfigChanel(dio_port_t port, dio_pin_t pin,dio_dir_t dir)
{
	switch(port)
	{
	case DIO_PORTA:
		if (dir == DIO_INPUT)
		{
			CLEAR_BIT(DIO_DDRA_REG,pin);
		}
		else
		{
			SET_BIT(DIO_DDRA_REG,pin);
		}
		break;

	case DIO_PORTB:
		if (dir == DIO_INPUT)
		{
			CLEAR_BIT(DIO_DDRB_REG,pin);
		}
		else
		{
			SET_BIT(DIO_DDRB_REG,pin);
		}
		break;

	case DIO_PORTC:
		if (dir == DIO_INPUT)
		{
			CLEAR_BIT(DIO_DDRC_REG,pin);
		}
		else
		{
			SET_BIT(DIO_DDRC_REG,pin);
		}
		break;

	case DIO_PORTD:
		if (dir == DIO_INPUT)
		{
			CLEAR_BIT(DIO_DDRD_REG,pin);
		}
		else
		{
			SET_BIT(DIO_DDRD_REG,pin);
		}
		break;
	}
}

void Dio_vidwriteChanel(dio_port_t port, dio_pin_t pin,dio_level_t level)
{
	switch (port)
	{
	case DIO_PORTA:
		if (level == DIO_HIGH)
		{
			SET_BIT(DIO_PORTA_REG,pin);
		}
		else
		{
			CLEAR_BIT(DIO_PORTA_REG,pin);
		}
		break;

	case DIO_PORTB:
		if (level == DIO_HIGH)
		{
			SET_BIT(DIO_PORTB_REG,pin);
		}
		else
		{
			CLEAR_BIT(DIO_PORTB_REG,pin);
		}
		break;

	case DIO_PORTC:
		if (level == DIO_HIGH)
		{
			SET_BIT(DIO_PORTC_REG,pin);
		}
		else
		{
			CLEAR_BIT(DIO_PORTC_REG,pin);
		}
		break;

	case DIO_PORTD:
		if (level == DIO_HIGH)
		{
			SET_BIT(DIO_PORTD_REG,pin);
		}
		else
		{
			CLEAR_BIT(DIO_PORTD_REG,pin);
		}
		break;
	}
}

void Dio_vidwritechanelgroup(dio_port_t port, u8 data,u8 mask)
{
	switch(port)
	{
	case DIO_PORTA:
		DIO_PORTA_REG = (DIO_PORTB_REG & mask)| (data);
		break;

	case DIO_PORTB:
		DIO_PORTB_REG =	(DIO_PORTB_REG & mask) |( data);
		break;

	case DIO_PORTC:
		DIO_PORTC_REG =	(DIO_PORTC_REG & mask) |( data);
		break;

	case DIO_PORTD:
		DIO_PORTD_REG =	(DIO_PORTD_REG & mask) |( data);
		break;
	}
}

dio_level_t Dio_udtreadChanel(dio_port_t port, dio_pin_t pin)
{
	dio_level_t loc_result = DIO_LOW;

	switch (port)
	{
	case DIO_PORTA:
		if (CHECK_BIT(DIO_PINA_REG,pin) == 1)
		{
			loc_result = DIO_HIGH;
		}
		else
		{
			loc_result = DIO_LOW;
		}
		break;

	case DIO_PORTB:
		if (CHECK_BIT(DIO_PINB_REG,pin) == 1)
		{
			loc_result = DIO_HIGH;
		}
		else
		{
			loc_result = DIO_LOW;
		}
		break;

	case DIO_PORTC:
		if (CHECK_BIT(DIO_PINC_REG,pin) == 1)
		{
			loc_result = DIO_HIGH;
		}
		else
		{
			loc_result = DIO_LOW;
		}
		break;

	case DIO_PORTD:
		if (CHECK_BIT(DIO_PIND_REG,pin) == 1)
		{
			loc_result = DIO_HIGH;
		}
		else
		{
			loc_result = DIO_LOW;
		}
		break;
	}
	return loc_result;
}

void Dio_vidflipChanel(dio_port_t port, dio_pin_t pin)
{
	switch (port)
	{
	case DIO_PORTA:
		FLIP_BIT(DIO_PORTA_REG,pin);
		break;

	case DIO_PORTB:
		FLIP_BIT(DIO_PORTB_REG,pin);
		break;

	case DIO_PORTC:
		FLIP_BIT(DIO_PORTC_REG,pin);
		break;

	case DIO_PORTD:
		FLIP_BIT(DIO_PORTD_REG,pin);
		break;
	}
}


void Dio_vidPullUpEn(dio_port_t port, dio_pin_t pin)
{
	switch (port)
	{
	case DIO_PORTA:
		SET_BIT(DIO_PORTA_REG,pin);
		break;

	case DIO_PORTB:
		SET_BIT(DIO_PORTB_REG,pin);
		break;

	case DIO_PORTC:
		SET_BIT(DIO_PORTC_REG,pin);
		break;

	case DIO_PORTD:
		SET_BIT(DIO_PORTD_REG,pin);
		break;
	}
}



u8   Dio_GetPinValue(u8 Copy_U8_Num)
{
	u8 Local_U8_Pin  = Copy_U8_Num % 10;
	u8 Local_U8_Port = Copy_U8_Num / 10;
	u8 Local_U8_Reading = 0;
	switch(Local_U8_Port)
	{
	case 1: Local_U8_Reading = CHECK_BIT(DIO_PINA_REG,Local_U8_Pin); break;
	case 2: Local_U8_Reading = CHECK_BIT(DIO_PINB_REG,Local_U8_Pin); break;
	case 3: Local_U8_Reading = CHECK_BIT(DIO_PINC_REG,Local_U8_Pin); break;
	case 4: Local_U8_Reading = CHECK_BIT(DIO_PIND_REG,Local_U8_Pin); break;
	default:                                                   break;
	}
	return Local_U8_Reading;
}

void Dio_vidSetPinDirection(u8 Copy_U8_Num ,u8 Copy_U8_State)
{
	u8 Local_U8_Pin  = Copy_U8_Num % 10;
	u8 Local_U8_Port = Copy_U8_Num / 10;
			switch(Copy_U8_State)
			{
			case INPUT :
				switch(Local_U8_Port)
				{
				case 1: CLEAR_BIT(DIO_DDRA_REG,Local_U8_Pin); break;
				case 2: CLEAR_BIT(DIO_DDRB_REG,Local_U8_Pin); break;
				case 3: CLEAR_BIT(DIO_DDRC_REG,Local_U8_Pin); break;
				case 4: CLEAR_BIT(DIO_DDRD_REG,Local_U8_Pin); break;
				default:                                break;
				}
				break;
			case OUTPUT:
				switch(Local_U8_Port)
				{
				case 1: SET_BIT(DIO_DDRA_REG,Local_U8_Pin); break;
				case 2: SET_BIT(DIO_DDRB_REG,Local_U8_Pin); break;
				case 3: SET_BIT(DIO_DDRC_REG,Local_U8_Pin); break;
				case 4: SET_BIT(DIO_DDRD_REG,Local_U8_Pin); break;
				default:                                break;
				}
				break;
				default:                                break;
			}
}

void Dio_vidSetPinValue(u8 Copy_U8_Num ,u8 Copy_U8_State)
{
	u8 Local_U8_Pin  = Copy_U8_Num % 10;
	u8 Local_U8_Port = Copy_U8_Num / 10;
			switch(Copy_U8_State)
			{
			case LOW :
				switch(Local_U8_Port)
				{
				case 1: CLEAR_BIT(DIO_PORTA_REG,Local_U8_Pin); break;
				case 2: CLEAR_BIT(DIO_PORTB_REG,Local_U8_Pin); break;
				case 3: CLEAR_BIT(DIO_PORTC_REG,Local_U8_Pin); break;
				case 4: CLEAR_BIT(DIO_PORTD_REG,Local_U8_Pin); break;
				default:                                 break;
				}
				break;
			case HIGH:
				switch(Local_U8_Port)
				{
				case 1: SET_BIT(DIO_PORTA_REG,Local_U8_Pin); break;
				case 2: SET_BIT(DIO_PORTB_REG,Local_U8_Pin); break;
				case 3: SET_BIT(DIO_PORTC_REG,Local_U8_Pin); break;
				case 4: SET_BIT(DIO_PORTD_REG,Local_U8_Pin); break;
				default:                                 break;
				}
				break;
				default:                                 break;
			}
}

void Dio_vidSetPinPullUpRes(u8 Copy_U8_Num,u8 Copy_U8_State)
{
	u8 Local_U8_Pin  = Copy_U8_Num % 10;
	u8 Local_U8_Port = Copy_U8_Num / 10;
			switch(Copy_U8_State)
			{
			case DISABLE :
				switch(Local_U8_Port)
				{
				case 1: CLEAR_BIT(DIO_PORTA_REG,Local_U8_Pin); break;
				case 2: CLEAR_BIT(DIO_PORTB_REG,Local_U8_Pin); break;
				case 3: CLEAR_BIT(DIO_PORTC_REG,Local_U8_Pin); break;
				case 4: CLEAR_BIT(DIO_PORTD_REG,Local_U8_Pin); break;
				default:                                 break;
				}
				break;
			case ENABLE:
				switch(Local_U8_Port)
				{
				case 1: SET_BIT(DIO_PORTA_REG,Local_U8_Pin); break;
				case 2: SET_BIT(DIO_PORTB_REG,Local_U8_Pin); break;
				case 3: SET_BIT(DIO_PORTC_REG,Local_U8_Pin); break;
				case 4: SET_BIT(DIO_PORTD_REG,Local_U8_Pin); break;
				default:                                 break;
				}
				break;
				default:                                 break;
			}
}
