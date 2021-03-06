/** 
 *@file communication.h
 *@brief this file's function is responsible for handling
 *data received from the host computer.
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <inc/tm4c123gh6pm.h>
#include <uart.h>
#include <movement.h>
#include <entertainment.h>
#include <sweep.h>
#include <ir.h>
#include <lcd.h>


/**
 * Input sent over UART is processed as a single char and switch executes intended function
 * Driver can move forward/backward, perform left/right turns, scan, play music, and change wheel speed.
 *
 *@param sensor, open interace object containing status of bot sensors
 *@author Tanner Dempsay
 *@date 4/16/2018
 */
char comCheck(oi_t *sensor);


#endif /* COMMUNICATION_H_ */
