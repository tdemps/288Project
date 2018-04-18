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
 
 int spdL = 50, spdH = 200;
char lock = 0;

/**
 * Input sent over UART is processed as a single char and switch executes intended function
 * Driver can move forward/backward, perform left/right turns, scan, play music, and change wheel speed.
 *
 *@param sensor, open interace object containing status of bot sensors
 *@author Tanner Dempsay
 *@date 4/16/2018
 */
char comCheck(oi_t *sensor){
	
    char data = toupper(uart_receive());
    lcd_printf("%c", data);
	if(lock && data == 'W'){
		uart_sendStr("Press 'L' to unlock forward movement\n");
		data = -1;
	}else if(lock && data == 'L'){
		uart_sendStr("Forward movement unlocked \n");
		lock = 0;
	}
	switch(data){
		case 'W':
				lock = move_forward(sensor,1,spdH);
				break;
		case 'A':
				turn_ccw(sensor, 1, spdL);
				break;
		case 'S':
				move_backward(sensor,1,spdH);
				break;
		case 'D':
				turn_cw(sensor, 1, spdL);
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
		case '2':
		        playSong(0);
		        break;
		case '3':
		        playSong(0);
		        break;
		case '4':
		        playSong(3);
		        break;
		case '5':
		        playSong(4);
		        break;
		case 'B':
		          stop();
		          break;
	    default:
				break;
	}
	return data;
}
