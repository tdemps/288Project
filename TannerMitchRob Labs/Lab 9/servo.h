/*
 * servo.h
 *
 *  Created on: Mar 21, 2018
 *      Author: tdempsay
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <lcd.h>
#include "timer.h"
#include "button.h";

int main(void);
void servo_init(void);
int servo_getAngle(void);
void servo_moveServo(int degrees, int dir);
void send_pulse(void);


#endif /* SERVO_H_ */
