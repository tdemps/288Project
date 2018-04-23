/** 
 *@file servo.h
 *@brief this file's methods allow for controlling
 * the onboard servo motor.
 *
 *@author Big Bird
 *
 *@date 4/16/2018
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <lcd.h>
#include <Timer.h>
#include "stdlib.h"
#include <stdbool.h>
#include "button.h"

///sets up TIMER1B for servo use
/**
  * Initializes pin PB5 for use with servo motor.
  * Sets up TIMER1B for PWM output.
  */
void servo_init(void);

/**
  * Returns current angle (0-180) of the servo motor in degrees.
  */
int servo_getAngle(void);

///Moves servo and updates angle
/**
  * Moves the servo certain number of degrees and updates angle variable.
  * dir > 1 for clockwise, < 1 for counterclockwise.
  *@param degrees  number of degrees to turn the servo motor.
  *@param dir  direction to turn the motor.
  */
void servo_moveServo(int degrees, int dir);


#endif /* SERVO_H_ */
