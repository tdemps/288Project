/*
 * sensors.h
 *
 *  Created on: Apr 15, 2018
 *      Author: alkoenen
 */

#ifndef SENSORS_H_
#define SENSORS_H_





#endif /* SENSORS_H_ */


#include "open_interface.h"
#include "uart.h"

int closeTo(int value, int target, int range);

int sensors_CheckCliff(oi_t *sensor_data);

int sensors_CheckBorder(oi_t *sensor_data);


