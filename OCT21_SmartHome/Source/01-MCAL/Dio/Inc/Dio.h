/*
 * Dio.h
 *  Created on: Aug , 2022
 *  Author: Mido Ayman
 */

#ifndef DIO_H_
#define DIO_H_

#include "Dio_Reg.h"
#include "Dio_Types.h"
#include "Bit_Math.h"
#include "Std_Types.h"

void Dio_vidconfigChanel(dio_port_t port, dio_pin_t pin,dio_dir_t dir);
void Dio_vidwriteChanel(dio_port_t port, dio_pin_t pin,dio_level_t level);
void Dio_vidwritechanelgroup(dio_port_t port, u8 data,u8 mask);
dio_level_t Dio_udtreadChanel(dio_port_t port, dio_pin_t pin);
void Dio_vidflipChanel(dio_port_t port, dio_pin_t pin);
void Dio_vidPullUpEn(dio_port_t port, dio_pin_t pin);


void Dio_vidSetPinValue(u8 Copy_U8_Num ,u8 Copy_U8_State);
u8   Dio_GetPinValue(u8 Copy_U8_Num);


#endif /* DIO_H_ */
