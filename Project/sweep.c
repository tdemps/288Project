/*
 * sweep.c
 *
 *  Created on: Mar 27, 2018
 *      Author: tdempsay
 */

#include "sweep.h"
#include <stdbool.h>
#include <math.h>
//char pass[10] = "cpre288psk";

int sweep(void){


    unsigned long pulseVal;
    int irVal = 0, servoAngle = 0, dir = 1, flag = 0 , startAng = 0, endAng = 0, lastPulse = 100, i = 0, lastIr = 90;
    int objDist[10] = {0,0,0}, objWidth[10] = {0,0,0}, objAngs[10] = {0,0,0};
	char str[100];

    lcd_init();
    ADC_init();
    pulse_init();
    servo_init();
    timer_waitMillis(50);
	uart_init();
	//WiFi_start(pass);
    timer_waitMillis(500);
	sprintf(str, "%-20s %-20s %-20s \n \n", "Degrees", "IR Distance (cm)", "Sonar Distance (cm)");
	uart_sendStr(str);

    while(servoAngle <= 180 && servoAngle >= 0){
        irVal = ir_getDist()*2;
       pulseVal = pulse_getDist();  //update distance values
        if(pulseVal > 100) pulseVal = 100;  //cap sensor values no remove noise
        if(irVal > 80) irVal = 80;
		if( ( ( ( abs(lastIr-irVal) > 25) && abs(pulseVal - lastPulse) > 20) || (lastIr < 60 && irVal < 60) ) && !flag){   //edge of object
			startAng = servoAngle;
			flag++;
		}
		   if(pulseVal < 99 && lastPulse < 99  && irVal < 79 && lastIr > 79 && flag) flag = 0;    //if first edge detection was a mistake
		if(flag && ( (irVal > 70) || ( pulseVal > lastPulse+30 ) ) ){  //if second edge detected
		    endAng = servoAngle;
			objDist[i] = lastIr;
			objWidth[i] = sin((endAng-startAng) * 3.14159/360) * objDist[i] * 2;    //width calculation
			objAngs[i] = (int) ((endAng+startAng) / 2);
			flag = 0;
			i = (i +1) % 9;
		}
        lcd_printf("IR: %d \n Pulse: %lu \n Angle: %d \n Objs: %d   Flag: %d", irVal, pulseVal, servoAngle, i, flag);

		sprintf(str, "%-20d %-20d %-20lu %-20d \n", servoAngle, irVal, pulseVal, flag); //string to send to putty
	    uart_sendStr(str);
		lastPulse = pulseVal;   //keep current distance for next loop
		lastIr = irVal;
        timer_waitMillis(75);
        servo_moveServo(1, dir);    //increment servo
        servoAngle = servo_getAngle();
    }

    int j, objAng = 0, smallest = 100;
    for(j = 0; j < i; j++){
        if(smallest > objWidth[j]){
            smallest = objWidth[j]; //find smallest object
            objAng = objAngs[j];
        }
    }

    servo_moveServo(180-objAng, -1);    //move to smallest object

    lcd_printf(" objects: %d, \n smallest width: %d \n Angle: %d", i , smallest, objAng);

    return 0;

}

