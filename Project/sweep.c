/** 
 *@file sweep.c
 *@brief this file contains methods to scan
 * for objects in front of the cyBot.
 *
 *@author somebody
 *
 *@date 4/20/2018
 */

#include "sweep.h"
#include <math.h>
#include <sweep.h>

/**
 * Performs a 180 degree sweep with the servo,
 * scanning for objects with the IR and pulse sensors.
 * Returns 0 once complete.
 */
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
		
        if(pulseVal > 80) pulseVal = 80;  //cap sensor values to 80cm
        if(irVal > 80) irVal = 80;
		
		//if( ( ( abs(lastIr-irVal) > 15 && abs(pulseVal - lastPulse) > 15) || (lastIr < 70 && irVal < 70) ) && !flag){
        if( ( ((lastPulse-pulseVal) > 15 && irVal < 79) || (lastIr < 75 && irVal < 75) ) && !flag){//first edge of object
			startAng = servoAngle;
			flag++;
		}

		if(pulseVal > 79 && lastPulse > 79  && irVal > 79 && lastIr > 79 && flag) flag = 0;    //if first edge detection was a mistake
		
		if(flag && ( (irVal > 79) || ( pulseVal > lastPulse+30 ) ) ){  //if second edge detected
		    endAng = servoAngle;
			objDist[i] = lastPulse;
			objWidth[i] = tan( (double) (endAng-startAng) * 3.14159/360) * objDist[i]*2;    //width calculation
			objAngs[i] = (int) ((endAng+startAng) / 2);
			flag = 0;
			if(objWidth[i] > 0)
			    sendInfo(objAngs[i],objDist[i],objWidth[i]);
			i++;
		}
        lcd_printf("Angle: %d \n Flag: %d",servoAngle, flag);

		sprintf(str, "%-15d %-20d %-15lu %-15d \r\n", servoAngle, irVal, pulseVal, flag); //string to send to putty
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

/**
  * Sends object info over UART connection via
  * string with format "object width distance degree".
  *
  */
void sendInfo(int deg, int distance, int width){
	
	char str[50];
	sprintf(str, "object %d %d %d \r\n", width, distance, deg);
	uart_sendStr(str);
	
}

