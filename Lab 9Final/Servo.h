/*
 * Servo.h
 *
 *  Created on: Mar 28, 2018
 *      Author: alkoenen
 */

#ifndef SERVO_H_
#define SERVO_H_


#include "lcd.h"
#include "Timer.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "Math.h"
#include "button.h"

void SERVO_INIT(void);

void TIMER_INIT(void);

void setToDegree(int degrees);

int buttonMove(int degrees, int direction);

int okToMove(void);

void printResults(void);

void setPulseByButton(void);




#endif /* SERVO_H_ */
