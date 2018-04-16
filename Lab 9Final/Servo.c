#include "lcd.h"
#include "Timer.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "Math.h"
#include "button.h"

volatile uint32_t pwm_period = 320000;
volatile uint32_t pwm_match = 282880;
volatile uint32_t lastButton=0;
volatile int direction = 1;
volatile int degree = 0;
//cy 25
// pwm_match = 297920;//middle
//volatile uint32_t pwm_left = 284800;//left
//pwm_match = 313600;//right

//cy 8
// pwm_match = 297520;//middle
volatile uint32_t pwm_left = 282880;//left
//pwm_match = 312160;//right
void SERVO_INIT(void){
        //enable clock for GPIO R1 to port
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

        //enable alernate functions on port PB3
        GPIO_PORTB_AFSEL_R |= BIT5;

        //enable timer on port B pins 5
        GPIO_PORTB_PCTL_R |= 0x700000;

        //set pin 5 to digital
        GPIO_PORTB_DEN_R |= BIT5;

        //set port 5 to output
        GPIO_PORTB_DIR_R |= 0x20;

}

void TIMER_INIT(void){
    //Enable Timer1
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;

    //Disable timer (clear bit TnEN in GPTMCTL)
    TIMER1_CTL_R &= ~TIMER_CTL_TBEN;

    //set configuration to 2 timers
    TIMER1_CFG_R = 0x4;

    //Set to PWM mode
    TIMER1_TBMR_R |= 0x008;

    //set to periodic timer mode
    TIMER1_TBMR_R |= 0x2;




    //set Period
    TIMER1_TBILR_R = pwm_period & 0x0000FFFF;
    TIMER1_TBPR_R = pwm_period >> 16;

    //set Match
    TIMER1_TBMATCHR_R = pwm_match & 0x0000FFFF;
    TIMER1_TBPMR_R = pwm_match >> 16;
    //enable timer 1A after changing settings
    TIMER1_CTL_R |= TIMER_CTL_TBEN;
}

void setToDegree(int degrees){
    if((degrees <=180) && (degrees>=0)){//check for a valid degree reading
        //set up match value
        pwm_match = pwm_left + 160 * degrees;
        //input into match register
        TIMER1_TBMATCHR_R = pwm_match & 0x0000FFFF;
        TIMER1_TBPMR_R = pwm_match >> 16;
        //update degrees
        degree = degrees;
    }
}

int buttonMove(int degrees, int direction){
    if(direction == -1){//going counter clockwise
        pwm_match = pwm_match - degrees * 160;
        TIMER1_TBMATCHR_R = pwm_match & 0x0000FFFF;
        TIMER1_TBPMR_R = pwm_match >> 16;
        degree = degree - degrees;
    }

    else if(direction == 1){//going clockwise
        pwm_match = pwm_match + degrees * 160;
                TIMER1_TBMATCHR_R = pwm_match & 0x0000FFFF;
                TIMER1_TBPMR_R = pwm_match >> 16;
                degree = degree + degrees;
    }
    return degree;

}

int okToMove(void){//checks to make sure it doesn't turn past the max to break the servo
    if(direction ==1 && degree >= 180){//dont go past full right
        return 0;
    }
    else if(direction ==-1 && degree <=0){//dont go past full left
        return 0;
    }
    return 1;
}
void printResults(void){
    if(direction ==1){
    lcd_printf("Mode:Incrementing\nPosition:%.1lf", degree);
    }
    else{
    lcd_printf("Mode:Decrementing\nPosition:%.1lf", degree);
    }
}

void setPulseByButton(void){
    uint32_t button = button_getButton();
    if(okToMove()){
    if(button ==0){// do nothing
        lastButton = 0;
    }
    if((button ==6) && (lastButton != 6)){//move one degree
           buttonMove(1, direction);
           lastButton =6;
    }
    else if((button ==5)&& (lastButton != 5)){//move 2.5 degrees
        buttonMove(2.5, direction);
        lastButton =5;
    }
    else if((button ==4)&& (lastButton != 4)){//move 5 degrees

        buttonMove(5, direction);
        lastButton =4;
    }
    }
    if((button == 3)&& (lastButton != 3)){//change direction
        if(direction == -1){
            direction = 1;

        }
        else if(direction == 1){
            direction = -1;

        }
        lastButton =3;
    }
    //printResults();
}




