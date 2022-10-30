/*
 * Dio_Types.h
 *
 *  Created on: Aug , 2022
 *      Author: Mido Ayman
 */

#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_


typedef enum
{
	DIO_PORTA,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}dio_port_t;


typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}dio_pin_t;


typedef enum
{
	DIO_INPUT,
	DIO_OUTPUT
}dio_dir_t;


typedef enum
{
	DIO_LOW,
	DIO_HIGH
}dio_level_t;


#define INPUT             0
#define OUTPUT            1
#define LOW               0
#define HIGH              1
#define DISABLE           0
#define ENABLE            1






#endif /* DIO_TYPES_H_ */
