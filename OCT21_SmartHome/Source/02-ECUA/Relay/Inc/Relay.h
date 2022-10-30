/*
 * Relay.h
 *
 * Created on: Oct , 2022
 * Author: Youssef Ali
 */ 


#ifndef RELAY_H_
#define RELAY_H_

/*****************************************_MACROS_*****************************************/
#define F_CPU	16000000UL

/****************************************_INCLUDES_***************************************/
#include "Dio.h"
#include <util/delay.h>

/***************************************_PROTOTYPES_***************************************/
void	Relay_Init		(void);
void	Relay_On			(void);
void	Relay_Off		    (void);




#endif /* RELAY_H_ */
