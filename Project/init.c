/** 
 *@file init.c
 *@brief this file contains methods initializing cyBot instruments
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
 */
#include <init.h>

///initializes all project critical functions.
/**
 * This method calls setup functions for lcd,adc/ir,pulse sensor, servo_init
 * and uart, each function contained in its corresponding library
 */
void initAll(){

	lcd_init();
	ADC_init();
	pulse_init();
	servo_init();
	uart_init();

}
