/*
 * Sonar.h
 *
 *  Created on: Mar 28, 2018
 *      Author: alkoenen
 */

#ifndef SONAR_H_
#define SONAR_H_

#include "lcd.h"
#include "Timer.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "Math.h"

void PING_INIT(void);

void TIMER3B_Handler(void);

void TIMER_INITSONAR(void);

void send_pulse(void);

unsigned int ping_read(void);




#endif /* SONAR_H_ */
