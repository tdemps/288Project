#include "communication.h"

/** 
 *@file communication.c
 *@brief this file's function is responsible for handling
 *data received from the host computer.
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
 */
 

 int spdL = 50, spdH = 180; //variables used in correlation to the bots speed in given direction
char lock = 0; //variable that was used as a flag to check whether the bot was locked or not

///program reads in a char and executes assigned bot function
/**
 * Input sent over UART is processed as a single char and switch executes intended function
 * Driver can move forward/backward, perform left/right turns, scan, play music, and change wheel speed.
 *
 *@param sensor, open interace object containing status of bot sensors
 *
 */
char comCheck(oi_t *sensor){
	char string2[50];
    char data = toupper(uart_receive());
    //lcd_printf("%c", data);

	if(lock && data == 'W'){
		uart_sendStr("Press 'L' to unlock forward movement\n");
		data = 0;
	}else if(lock && data == 'L'){
		uart_sendStr("Forward movement unlocked \n");
		lock = 0;
	}
	switch(data){
		case 'W':   //moves bot fowards, returns > 0 if move was stopped by sensor
				lock = move_forward(sensor,10,spdH);
			
				break;
		case 'A':   //counterclockwise turn
				turn_ccw(sensor, 8, spdL);
				break;
		case 'S':   //moves bot backwards
				move_backward(sensor,10,spdH);
				break;
		case 'D':   //clockwise turn
				turn_cw(sensor, 8, spdL);
				break;
		case 'N':	//decreased forward/reverse speed
				spdH = (spdH-10) > 10 ? (spdH-10) : 10;
				break;
		case 'M':	//decreased forward/reverse speed
				spdH = (spdH+10) < 200 ? (spdH+10) : 200;
				break;
	    case 'L':	//unlock forward movement
	            lock = 0;
				break;
		case 'T':	//scan for objects
		        sweep();
		        break;
		case '1':
		        playSong(0);
				break;
		case 'I':
		        ir_getDist();
		        break;
	    default:
				break;
	}
	return data;
}
