/** 
 *@file ir.h
 *@brief this file contains methods for measuring
 * distance with the ir sensor
 *the cyBot.
 *
 *@author Tanner Dempsay
 *
 *@date 4/20/2018
 */

#ifndef IR_H_
#define IR_H_

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <lcd.h>
#include <math.h>
#include <Timer.h>

///sets up IR sensor components
/**
 * Initializes Pin PB4 for ADC0 and AIN10 for sampling
 * the IR sensors output.
 *
 */
void ADC_init(void);

///returns digital value from IR sensor
/**
 * Starts ADC conversion and waits for value to be received, returns
 * digital value processed by ADC0.
 *
 */
unsigned ADC_read(void);

///returns object distance from IR in cm.
/**
 * Reads 20 values from IR sensor and averages them, then
 * converts digital value to centimeters.
 *
 */
int ir_getDist(void);


#endif /* SERVO_H_ */
