/*
 * sweep.h
 *
 *  Created on: Mar 27, 2018
 *      Author: tdempsay
 */

#ifndef SWEEP_H_
#define SWEEP_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include <lcd.h>
#include <Timer.h>
#include <pulse.h>
#include <ir.h>
#include <servo.h>
#include <stdbool.h>
#include <uart.h>

///scans for objects in front of cyBot
/**
 * Performs a 180 degree sweep with the servo,
 * scanning for objects with the IR and pulse sensors.
 * Returns 0 once complete.
 */
int sweep(void);

///sends found object info to host
/**
  * Sends object info over UART connection via
  * string with format "object width distance degree".
  */
void sendInfo(int deg, int distance, int width);

#endif /* SWEEP_H_ */
