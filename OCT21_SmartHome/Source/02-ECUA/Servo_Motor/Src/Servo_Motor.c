/*
 * Servo_Motor.c
 *
 *  Created on: Oct , 2022
 *      Author: Youssef Ali
 */

#include "Dio.h"
#include "Servo_Motor.h"
#include "TIMER1_REG.h"
#include "Std_Types.h"
#include <util/delay.h>
#include "Lcd.h"
#include "Hc05.h"

void ServoMotor_VidInit(void)
{
	// make OC1A pin as output
	DIO_DDRD_REG |= (1<<DIO_PIN5);


	// set timer1 counter as zero
	u32 loc_TCNT1_val = 0;
	TIMER1_TCNT1H_REG = loc_TCNT1_val>>8;
	TIMER1_TCNT1L_REG = loc_TCNT1_val;

	// set top count for timer1 PWM frequency=50 Hz

	u32 loc_ICR1_val= 4999;
	TIMER1_ICR1H_REG = loc_ICR1_val>>8;
	TIMER1_ICR1L_REG = loc_ICR1_val;

	// set FAST PWM, clear OC1A, Prescaler=64
	TIMER1_TCCR1A_REG = (1<<WGM11)|(0<<WGM10)|(1<<COM1A1);
	TIMER1_TCCR1B_REG = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);

}




void ServoMotor_VidOpenDoor(void)
{

	// open door and position shaft at 90ú

	u32 loc_OCR1A_val = 350;

	TIMER1_OCR1AH_REG = loc_OCR1A_val>>8;

	TIMER1_OCR1AH_REG = loc_OCR1A_val;

	// delay until motor stop

	_delay_ms(1000);
}



void ServoMotor_VidCloseDoor(void)
{
	// open door and position shaft at 180ú

	u32 loc_OCR1A_val = 130;

	TIMER1_OCR1AH_REG = loc_OCR1A_val>>8;

	TIMER1_OCR1AH_REG = loc_OCR1A_val;

	// delay until motor stop

	_delay_ms(1000);
}


void ServoMotor_VidSwitchDoor (Door_State_t *DoorOpened)
{
  if (*DoorOpened == 0)
  {
    Lcd_vidCmd(_LCD_CLEAR);
    Lcd_vidRowColumn(0, 0);
    Lcd_vidDisplayStr("Door Is Opened");
    Hc05_SendString("Door Is Opened");
    ServoMotor_VidOpenDoor();
    _delay_ms(500);
    *DoorOpened = OPENED;
  }
  else
  {
	Lcd_vidCmd(_LCD_CLEAR);
    Lcd_vidRowColumn(0, 0);
    Lcd_vidDisplayStr("Door Is Closed");
    Hc05_SendString("Door Is Closed");
    ServoMotor_VidCloseDoor();
    _delay_ms(500);
    *DoorOpened = CLOSED;
  }

}

void ServoMotor_VidCheckDoor(u8 DoorState)
{
  if (DoorState == OPENED)
  {
    Lcd_vidRowColumn(1, 0);
    Lcd_vidDisplayStr("Door Is Opened");
    Hc05_SendString("Door Is Opened");

  }
  else
  {
	Lcd_vidRowColumn(1, 0);
	Lcd_vidDisplayStr("Door Is Closed");
    Hc05_SendString("Door Is Closed");

  }

}
