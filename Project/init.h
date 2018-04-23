/** 
 *@file init.h
 *@brief this file contains methods initializing cyBot instruments
 *
 *@author somebody
 *
 *@date 4/15/2018
 */

#ifndef INIT_H_
#define INIT_H_
#include <stdio.h>
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <lcd.h>
#include <pulse.h>
#include <ir.h>
#include <servo.h>
#include <uart.h>
#include <entertainment.h>
///initializes all project critical functions.
/**
 * This method calls setup functions for lcd,adc/ir,pulse sensor, servo_init
 * and uart, each function contained in its corresponding library
 */
void initAll();



#endif /* INIT_H_ */
