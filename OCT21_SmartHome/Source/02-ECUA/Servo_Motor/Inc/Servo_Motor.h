/*
 * Servo_Motor.h
 *
 *  Created on: Oct , 2022
 *      Author: Youssef Ali
 */

#ifndef SOURCE_02_ECUA_SERVO_MOTOR_INC_SERVO_MOTOR_H_
#define SOURCE_02_ECUA_SERVO_MOTOR_INC_SERVO_MOTOR_H_

#include "Servo_Motor_Types.h"


void ServoMotor_VidInit(void);

void ServoMotor_VidOpenDoor(void);

void ServoMotor_VidCloseDoor(void);

void ServoMotor_VidSwitchDoor (Door_State_t *DoorOpened);

void ServoMotor_VidCheckDoor(Door_State_t DoorState);


#endif /* SOURCE_02_ECUA_SERVO_MOTOR_INC_SERVO_MOTOR_H_ */
