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
#include "timer.h"
#include "pulse.h"
#include "ir.h"
#include "servo.h"
#include <stdbool.h>
#include "uart.h"

int sweep(void);

void sendInfo(int deg, int distance, int width);

#endif /* SWEEP_H_ */
