/** 
 *@file pulse.h
 *@brief this file allows for initializing and 
 *send pulses and get distance via the pulse sensor.
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
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

///handles edge events
/**
 * This method is the ISR for timer3B, captures timer values
 * at edges of pulse and resets interrupt flag.
 */
void TIMER3B_Handler(void);

///Initializes pulse sensor with timer3B
/**
 * Initializes pin B3 and timer3B for use with pulse sensor. 
 * Timer captures edges of pulse sensor ouptut.
 */
void pulse_init(void);

///starts pulse reading of distance.
/**
 * Sends an output high signal to PB3 (pulse sensor) initialize a distance reading.
 *Sets PB3 to input afterwards. 
 */
void send_pulse(void);

///returns object distance using pulse sensor.
/**
 * Initializes a pulse and waits for receiving pulse.
 * Computes and returns the distance of object in cm.
 * in cm.
 */
unsigned long pulse_getDist(void);



#endif /* PULSE_H_ */
