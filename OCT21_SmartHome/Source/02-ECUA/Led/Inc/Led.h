/*
 * Led.h
 *
 *  Created on: Sep , 2022
 *	Author: Youssef Galal
 */

#ifndef SOURCE_02_ECUA_LED_INC_LED_H_
#define SOURCE_02_ECUA_LED_INC_LED_H_

#include "Led_Types.h"


void Led_vidinit(void);
void Led_vidledOn(led_ledId_t ledId);
void Led_vidledOff(led_ledId_t ledId);
void Led_vidledToggle(led_ledId_t ledId);


#endif /* SOURCE_02_ECUA_LED_INC_LED_H_ */
