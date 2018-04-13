#include "communication.h"

//assumes uart is configured.

/**
 *Input sent of UART is processed as a single char and switch executes intended control.
 *Driver can move forward/backward, perform left/right turns, scan, play music, and change wheel speed.
 *@param sensor, open interace object containing status of bot sensors
 */
 int spdL = 100, spdR = 100;
 
int void comCheck(oi_t *sensor){	
    char data = toupper(uart_receive());
	if(lock)
		uart_sendStr("Press 'L' to unlock movement");
	if(data == 'W' || data == 'A' || data == 'S' || data == 'D')
		data = -1;
	
	switch(data){
		case 'W':
				move_forward(sensor,spdR,spdL);
				break;
		case 'A':
				//turnccw
				break;
		case 'S':
				move_backward(sensor,spdR,spdL);
				break;
		case 'D':
				break;
		case 'N':
				SpdR = spdL = ( (spdR-10) > 0 ? (spdR-10) : 0;
				break;
		case 'M':
				SpdR = spdL = ( (spdR+10) < 150 ? (spdR+10) : 150;
				break;
	    case 'L': lock = 0;
				break;
		case 'T': //sweep
				break;
	    default:
				break;
	}
}