/** 
 *@file movement.c
 *@brief this file contains methods for moving
 *the cyBot.
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
 */

#include "movement.h"

//Calibration constants - change when using different bots
#define CALIB_L 0
#define CALIB_R 0

/**
 * Moves the bot forward a certain distance at a set speed.
 * Checks front sensors every cm while moving.
 * @param sensor - open interface sensor pointer
 * @param centimeters - how far the bot will travel forward
 * @param spd - speed, how fast the wheels will turn
 *
 * Sends a char to UART, 0 - 4, depending on if the bot encountered anything while moving.
 * @date 4/16/18
 * @author Tanner Dempsay
 * Return 0 if clear.
 * Return 1 if left bumper hit.
 * Return 2 if right bumper hit.
 * Return 3 if bot is in front of a cliff.
 * Return 4 if bot hit the boundary.
 */
char move_forward(oi_t *sensor, int centimeters, int spd) {
	//chack sensors on bot
    if (checkAll(sensor)) {
        return 1;
    }

    int sum = 0, hit = 0;
	char test = 0;

    oi_setWheels((spd+CALIB_L), (spd+CALIB_R)); // move forward;

    while (sum < centimeters*10) {
        oi_update(sensor);
		test = checkAll(sensor);
		
        if(test){
            uart_sendStr("Fwd Movement Stopped \n\r");
			break;
		}

        sum += sensor->distance;
    }

    stop();
    uart_sendStr("Fwd Movement Complete \n\r");

    return test;
}


/**
 * Turn the bot counterclockwise a certain amount and speed
 *
 * @param sensor - an open interface sensor pointer
 * @param degrees - how far the bot will turn
 * @param speed - how fast to turn
 * @author Tanner Dempsay
 * @date 4/16/18
 */
void turn_ccw(oi_t *sensor, int degrees, int speed) {

    int sum = 0;
    oi_setWheels(speed, -speed); // move forward;

    while (sum < degrees) {
        oi_update(sensor);
        sum += sensor->angle;
    }

    stop();

    uart_sendChar('6');
}

/**
 * Turn the bot clockwise a certain amount and speed
 *
 * @param sensor - an open interface sensor pointer
 * @param degrees - how far the bot will turn
 * @param speed - how fast to turn
 *
 * @author Tanner Dempsay
 * @date 4/16/18
 */
void turn_cw(oi_t *sensor, int degrees, int speed) {

    int sum = degrees;
    oi_setWheels(-speed, speed); // move forward;

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->angle;
    }

    stop();

    uart_sendChar('6');
}

///Move in reverse a certain distance
/**
 *
 * Similar to the function for moving forward.
 * While moving back, the cliff signals are checked to make sure the bot doesn't accidentally back up over the boundary.
 * Sends a 7 through UART to let the driver know the reverse completed successfully.
 * Sends a 4 if the boundary was hit.
 *
 * @param sensor - an open interface sensor pointer
 * @param centimeters - how far the bot will move backwards
 * @param spd - the speed at which the bot will move (speed of the motors)
 * @author Tanner Dempsay
 * @date 4/16/18
 */
void move_backward(oi_t *sensor, int centimeters, int spd) {

    int sum = centimeters * 10;
    oi_setWheels(-spd, -spd); // move forward;

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->distance;

        if (sensors_CheckBorder(sensor)) {
            break;
        }
    }

    stop();

    uart_sendChar('7');
}

///
/**
 * Stop the bot by disabling its motors
 * @author Tanner Dempsay
 * @date 4/16/2018
 */
void stop() {
    oi_setWheels(0, 0);
}


/**
 * Checks for left bumper, right bumper, cliff, and boundary sensors.
 * Run at the beginning of and during forward movement.
 * Returns char based on status of the sensors.
 * @param sensor - open interface sensor pointer
 * @date 4/16/2018
 * @author Tanner Dempsay
 */
char checkAll(oi_t *sensor) {
    char status = 0;

	if (sensor->bumpLeft && sensor->bumpRight) {
		//    status = '9';
        }
        else if (sensor->bumpLeft) {
		//	status = '1';
        }
        else if (sensor->bumpRight) {
        //    status = '2';
        }
        else if (sensors_CheckCliff(sensor)) {
		//	status = '3';
        }
        else if (sensors_CheckBorder(sensor)) {
      //      status = '4';
        }
	if(status){
		uart_sendStr(sprintf("Status: %c", status));
	//	return status;
	}
		
    return status;
}

