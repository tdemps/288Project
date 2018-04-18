/*
 * sweep.c
 *
 *  Created on: Mar 27, 2018
 *      Author: tdempsay
 */

#include "sweep.h"
#include <stdbool.h>
#include <math.h>
#include <sweep.h>

int sweep(void){

    unsigned long pulseVal;
    int irVal = 0, servoAngle = 0, dir = 1, flag = 0, startAng = 0, endAng = 0, lastPulse = 90, i = 0, lastIr = 90;
    int objDist[10] = {0,0,0,0,0}, objWidth[10] = {0,0,0,0,0}, objAngs[10] = {0,0,0,0,0};
	char str[100];
    uart_sendChar('\r'); uart_sendChar('\n');
    uart_sendStr("Beginning sweep \r\n");
    timer_waitMillis(500);
	//sprintf(str, "%-20s %-20s %-20s \n \n", "Degrees", "IR Distance (cm)", "Sonar Distance (cm)");
	//uart_sendStr(str);

    while(servoAngle <= 180 && servoAngle >= 0){
        irVal = ir_getDist()*2;
        pulseVal = pulse_getDist();  //update distance values
		
        if(pulseVal > 90) pulseVal = 90;  //cap sensor values to 80cm
        if(irVal > 90) irVal = 90;
		
		if( ( ( abs(lastIr-irVal) > 25 && abs(pulseVal - lastPulse) > 20) || (lastIr < 60 && irVal < 60) ) && !flag){   //first edge of object
			startAng = servoAngle;
			flag++;
		}

		if(pulseVal < 89 && lastPulse < 89  && irVal < 89 && lastIr > 89 && flag) flag = 0;    //if first edge detection was a mistake
		
		if(flag && ( (irVal > 80) || ( pulseVal > lastPulse+20 ) ) ){  //if second edge detected
		    endAng = servoAngle;
			objDist[i] = lastPulse;
			objWidth[i] = tan( (double) (endAng-startAng) * 3.14159/360) * objDist[i]*2;    //width calculation
			objAngs[i] = (int) ((endAng+startAng) / 2);
			flag = 0;
			sendInfo(objAngs[i],objDist[i],objWidth[i]);
			i++;
		}
        //lcd_printf("IR: %d \n Pulse: %lu \n Angle: %d \n Objs: %d   Flag: %d", irVal, pulseVal, servoAngle, i, flag);

		sprintf(str, "%-20d %-20d %-20lu %-20d \n", servoAngle, irVal, pulseVal, flag); //string to send to putty
	    uart_sendStr(str);
		lastPulse = pulseVal;   //keep current distance for next loop
		lastIr = irVal;
        timer_waitMillis(75);
        servo_moveServo(1, dir);    //increment servo
        servoAngle = servo_getAngle();
    }

    servo_moveServo(180, -1);    //move to smallest object

    return 0;
}

void sendInfo(int deg, int distance, int width){
	
	char str[50];
	sprintf(str, "object %d %d %d \r\n", width, distance, deg);
	//uart_sendChar('\r');
	uart_sendStr(str);
	
}

