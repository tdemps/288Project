/*
 * servo.c
 *
 *  Created on: Mar 21, 2018
 *      Author: tdempsay
 */

#include "lcd.h"
#include "String.h"
#include "Timer.h"
#include "stdlib.h"
#include <stdbool.h>
#include "button.h"

int angle = 0;
void servo_init(void){
    SYSCTL_RCGCGPIO_R |= 2;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_DEN_R |= 0x20;       //PB5
    GPIO_PORTB_PCTL_R |= 0x700000;
    GPIO_PORTB_DIR_R &= ~0x20;
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;

    TIMER1_CTL_R &= ~0x100;
    TIMER1_CFG_R |= TIMER_CFG_16_BIT;   //good
    TIMER1_TBMR_R = 0xA;    //count down, periodic mode, pwm enabled
    TIMER1_CTL_R &= ~0x400;
    TIMER1_TBPR_R = 0x4;    //prescaler (320000)
    TIMER1_TBILR_R = 0xE200; //good

	
	TIMER1_TBMATCHR_R = 23000;  //initial angle is 90, 37356
    TIMER1_TBPMR_R = 0x4;
	
    TIMER1_CTL_R |= 0x100;
}

int servo_getAngle(void){
	return angle;
}

void servo_moveServo(int degrees, int dir){
   //unsigned int pwm_period = 320,000
   // uint8_t button = 0;
   // int dir = 1;    //changes direction
   
    angle += degrees * dir;  //current position in degrees
	TIMER1_TBMATCHR_R += ((degrees * 150) * dir );
	//TIMER1_TBPMR_R += ((degrees * 150) * dir );
	return;
	
   // while(1){

//        button = button_getButton();
//        switch(button) {
//        //increments match
//        case 6: TIMER1_TBMATCHR_R += 156 * dir; angle+=1*dir; break;    //1 degrees
//        case 5: TIMER1_TBMATCHR_R += 390 * dir; angle+=2.5*dir; break;  //button actions    //2.5 degrees
//        case 4: TIMER1_TBMATCHR_R += 780 * dir; angle+=5*dir; break;    //5 degrees
//        case 3: dir *= -1;
       // }
        //lcd_printf("Angle: %.1f\nDir: %s",angle, (dir > 0) ? "Clockwise": "Counterclockwise");
        //timer_waitMillis(200);
   // }
}

