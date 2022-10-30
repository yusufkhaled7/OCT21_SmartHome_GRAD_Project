/*
 * TIMER1_REG.h
 *
 *  Created on: Oct , 2022
 *      Author: Youssef Ali
 */

#ifndef SOURCE_01_MCAL_TIMER1_INC_TIMER1_REG_H_
#define SOURCE_01_MCAL_TIMER1_INC_TIMER1_REG_H_

#include "Bit_Math.h"

#define TIMER1_TCCR1A_REG  (*(u8*)0x4F)
#define TIMER1_TCCR1B_REG  (*(u8*)0x4E)
#define TIMER1_TCNT1H_REG  (*(u8*)0x4D)
#define TIMER1_TCNT1L_REG  (*(u8*)0x4C)
#define TIMER1_OCR1AH_REG  (*(u8*)0x4B)
#define TIMER1_OCR1AL_REG  (*(u8*)0x4A)
#define TIMER1_OCR1BH_REG  (*(u8*)0x49)
#define TIMER1_OCR1BL_REG  (*(u8*)0x48)
#define TIMER1_ICR1H_REG   (*(u8*)0x47)
#define TIMER1_ICR1L_REG   (*(u8*)0x46)


typedef enum
{
	WGM10,
	WGM11,
	FOC1B,
	FOC1A,
	COM1B0,
	COM1B1,
	COM1A0,
	COM1A1

}TCCR1A_REG_t;

typedef enum
{
	CS10,
	CS11,
	CS12,
	WGM12,
	WGM13,
	RESERVED,
	ICES1,
	ICNC1

}TCCR1B_REG_t;



#endif /* SOURCE_01_MCAL_TIMER1_INC_TIMER1_REG_H_ */
