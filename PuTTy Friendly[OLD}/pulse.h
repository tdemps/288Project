/*
 * pulse.h
 *
 *  Created on: Mar 7, 2018
 *      Author: tdempsay
 */
#ifndef PULSE_H_
#define PULSE_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <lcd.h>
#include "timer.h"
#include <stdbool.h>
#include "C:/ti/TivaWare_C_Series-2.1.2.111/driverlib/interrupt.h"

int main(void);
void pulse_init(void);
void TIMER3B_Handler(void);
void send_pulse(void);
unsigned long pulse_getDist(void);


#endif /* PULSE_H_ */
