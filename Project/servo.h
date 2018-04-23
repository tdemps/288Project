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

/**
  * Initializes pin PB5 for use with servo motor.
  * Sets up TIMER1B for PWM output.
  *
  */
void servo_init(void);

/**
  * Returns current angle of servo in degrees.
  *
  */
int servo_getAngle(void);

/**
  * Moves the servo certain number of degrees.
  * dir > 1 for clockwise, < 1 for counterclockwise
  *
  */
void servo_moveServo(int degrees, int dir);


#endif /* SERVO_H_ */
