/*
 * KeyPad.h
 *
 *  Created on: Oct , 2022
 *      Author: Mido Ayman
 */

#ifndef HAL_KEYPAD_KEYPAD_INTERFACE_H_
#define HAL_KEYPAD_KEYPAD_INTERFACE_H_

#include "Std_Types.h"
#include <util/delay.h>
#include "Dio.h"
#include "KeyPad_Reg.h"

#define KEYPAD_PRESSED              0
#define KEYPAD_RELEASED             1

void Keypad_vidinit(void);
u8   Keypad_getChar(void);

#endif /* SOURCE_02_ECUA_LCD_INC_KEYPAD_H_ */
