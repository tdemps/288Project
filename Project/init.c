/** 
 *@file init.c
 *@brief this file contains the initializations
 * for all bot components needed for project functions.
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
 */
#include <init.h>

/**
 * This method calls setup functions for lcd,adc/ir,pulse sensor, servo_init
 * and uart.
 * @author Tanner Dempsay
 * @date 4/16/2018
 */
void initAll(){
	lcd_init();

	ADC_init();
	pulse_init();
	servo_init();
	uart_init();

	

	return;
}
