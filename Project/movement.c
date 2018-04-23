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

//Calibration constants for wheels
#define CALIB_L 0
#define CALIB_R 0

///moves the robot forward safely
/**
 * Moves the bot forward a certain distance at a set speed.
 * Checks front sensors every cm while moving and before movement.
 * @param sensor - open interface sensor pointer
 * @param centimeters - how far the bot will travel forward
 * @param spd - speed, how fast the wheels will turn
 *
 * Returns a nonzero char, depending on if the bot encountered anything while moving, 0 otherwise.
 * 
 */
char move_forward(oi_t *sensor, int centimeters, int spd) {
	//used to send partial movement info
    char str10[15];
	//update sensors for initial check
    oi_update(sensor);
    if (checkAll(sensor)) {
		///lets driver know movement is cancelled
		uart_sendStr("Fwd Movement Blocked \n\r");	
        return 1;	//blocks forward movement
		
    }
	
    int sum = 0;
	//status of front sensors
	char test = 0; 

    oi_setWheels((spd+CALIB_L), (spd+CALIB_R)); // engages wheels 

    while (sum < centimeters*10) {
        oi_update(sensor);
		test = checkAll(sensor);
		
        if(test){
            uart_sendStr("Fwd Movement Stopped \n\r");
            sprintf(str10, "move %d \n", sum/10);	//sends back partial movement status
            uart_sendStr(str10);
            stop();
            return test;	//return nonzero
		}

        sum += sensor->distance;
    }

    stop();
	uart_sendStr("move 10 \n");	//return distance for GUI processessing
    return test;
}

///turns bot counterclockwise by a number of degrees
/**
 * Turn the bot counterclockwise a certain amount and speed.
 * Sends string via UART to confirm complete turn is finished.
 *
 * @param sensor - an open interface sensor pointer
 * @param degrees - how far the bot will turn
 * @param speed - how fast to turn
 *
 */
int turn_ccw(oi_t *sensor, int degrees, int speed) {

    int sum = 0;
    oi_setWheels(speed, -speed); //engage wheels for counterclockwise movement

    while (sum < degrees) {
         oi_update(sensor);
         sum += sensor->angle;
    }

    stop();
	uart_sendStr("angle -10 \n");	

	return -degrees;
}
///Turns bot clockwise a certain number of degrees
/**
 * Turn the bot clockwise a certain amount and speed.
 * Sends string via UART to confirm complete turn is finished.
 *
 * @param sensor - an open interface sensor pointer
 * @param degrees - how far the bot will turn
 * @param speed - how fast to turn
 *
 */
int turn_cw(oi_t *sensor, int degrees, int speed) {

    int sum = degrees;
    oi_setWheels(-speed, speed); //engage wheels for clockwise movement

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->angle;
    }

    stop();
	uart_sendStr("angle 10 \n");

	return degrees;
}

///Move in reverse a certain distance
/**
 *
 * Similar to the function for moving forward.
 * Sends string via UART when backwards movement is complete.
 *
 * @param sensor - an open interface sensor pointer
 * @param centimeters - how far the bot will move backwards
 * @param spd - the speed at which the bot will move (speed of the motors)
 * 
 */
int move_backward(oi_t *sensor, int centimeters, int spd) {

    int sum = centimeters * 10;
    oi_setWheels(-spd, -spd); // move forward;

    while (sum > 0) {
        oi_update(sensor);
        sum += sensor->distance;

    }

    stop();
	uart_sendStr("move -10 \n");
	return -centimeters;
}

///stops wheels
/**
 * Stop the bot by disabling its motors.
 *
 */
void stop() {
    oi_setWheels(0, 0);
}

///checks all front sensors.
/**
 * Checks left bumper, right bumper, cliff, and boundary sensors.
 * Run at the beginning of and during forward movement.
 * Returns char based on status of the sensors.
 * @param sensor - open interface sensor pointer
 * 
 */
char checkAll(oi_t *sensor) {
    char status = 0;
    char string[20];
	
	if (sensor->bumpLeft && sensor->bumpRight) {
		    status = '9';
			
		    sprintf(string,"Bump left \r\n");
		    uart_sendStr(string);
		    sprintf(string,"Bump right \r\n");
		    uart_sendStr(string);
        }
        else if (sensor->bumpLeft) {
			status = '1';
			
			sprintf(string,"Bump left \r\n");
			uart_sendStr(string);
        }
        else if (sensor->bumpRight) {
			status = '2';
			
            sprintf(string,"Bump right \r\n");
            uart_sendStr(string);  
        }
        else if (sensors_CheckCliff(sensor)) {
			status = '3';
        }
        else if (sensors_CheckBorder(sensor)) {
           status = '4';
        }
		
    return status;
}

