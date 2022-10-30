/*
 * Eeprom.h
 *
 * Created: Oct , 2022
 * Author: Malek Elsaka
 */

#ifndef EEPROM_H
#define EEPROM_H

#include <Eeprom_Reg.h>
#include "Std_Types.h"

void EEPROM_Write(u16 address,u8 data);
u8 EEPROM_Read(u16 address);
#endif  /* EEPROM_H */
