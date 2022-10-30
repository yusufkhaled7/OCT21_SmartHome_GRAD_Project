/*
 * Lcd.h
 *
 *  Created on: Oct , 2022
 *      Author: Mido Ayman
 */

#ifndef SOURCE_02_ECUA_LCD_INC_LCD_H_
#define SOURCE_02_ECUA_LCD_INC_LCD_H_

#include "Std_Types.h"
#include "Lcd_Types.h"

#define LCD_MASK (0x0F)

void Lcd_vidinit(void);
void Lcd_vidDisplayChar(u8 chr);
void Lcd_vidDisplayStr(u8* str);
void Lcd_vidCmd(lcd_Cmd_t cmd);
void Lcd_vidRowColumn(u8 row, u8 col);
void Lcd_vidDisplayInt(u32 num);
void Lcd_vidDisplayFloat(f64 num);

#endif /* SOURCE_02_ECUA_LCD_INC_LCD_H_ */
