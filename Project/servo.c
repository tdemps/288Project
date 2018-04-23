/** 
 *@file servo.h
 *@brief this file's methods allow for controlling
 * the onboard servo motor.
 *
 *@author Big Bird
 *
 *@date 4/16/2018
 */
 
#include <servo.h>

int angle = 0; //Current angle of servo

///sets up TIMER1B for servo use
/**
  * Initializes pin PB5 for use with servo motor.
  * Sets up TIMER1B for PWM output.
  */
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

    TIMER1_TBMATCHR_R = 22300;  //initial angle is 90, 
    TIMER1_TBPMR_R = 0x4;
	
    TIMER1_CTL_R |= 0x100;
}

/**
  * Returns current angle (0-180) of the servo motor in degrees.
  */
int servo_getAngle(void){
	return angle;
}

///Moves servo and updates angle
/**
  * Moves the servo certain number of degrees and updates angle variable.
  * dir > 1 for clockwise, < 1 for counterclockwise.
  *@param degrees  number of degrees to turn the servo motor.
  *@param dir  direction to turn the motor.
  */
void servo_moveServo(int degrees, int dir){
   //unsigned int pwm_period = 320,000
   // int dir = 1;    //changes direction
   
    angle += degrees * dir;  //current position in degrees
	TIMER1_TBMATCHR_R += ((degrees * 150) * dir );
	//TIMER1_TBPMR_R += ((degrees * 150) * dir );
	return;
	
}

