#include "open_interface.h"
#include "uart.h"
#include <sensors.h>


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
char move_forward(oi_t *sensor, int centimeters, int speed);

///checks all front sensors.
/**
 * Checks left bumper, right bumper, cliff, and boundary sensors.
 * Run at the beginning of and during forward movement.
 * Returns char based on status of the sensors.
 * @param sensor - open interface sensor pointer
 * 
 */
char checkAll(oi_t *sensor);

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
int turn_ccw(oi_t *sensor, int degrees, int speed);

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
int turn_cw(oi_t *sensor, int degrees, int speed);

///Move in reverse a certain distance
/**
 *
 * Similar to the function for moving forward.
 * Sends string via UART when backwards movement is complete.
 *
 * @param sensor - an open interface sensor pointer
 * @param centimeters - how far the bot will move backwards
 * @param spd - the speed at which the bot will move (speed of the wheels)
 * 
 */
int move_backward(oi_t *sensor, int centimeters, int speed);

///stops wheels
/**
 * Stop the bot by disabling its motors.
 *
 */
void stop();
