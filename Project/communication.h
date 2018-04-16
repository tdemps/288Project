/*
 * communication.h
 *
 *  Created on: Apr 15, 2018
 *      Author: tdempsay
 */
#include <stdio.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "timer.h"
#include "pulse.h"
#include "ir.h"
#include "servo.h"
#include <stdbool.h>
#include "uart.h"
#include <movement.h>
#include <entertainment.h>

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


char comCheck(oi_t *sensor);


#endif /* COMMUNICATION_H_ */
