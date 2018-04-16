#include "lcd.h"
#include "Timer.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "Math.h"



volatile uint32_t falling_edge_time;
volatile uint32_t rising_edge_time;
volatile uint32_t overflows =0;
volatile enum {LOW,HIGH,DONE} state = DONE;

void PING_INIT(void){
    //enable clock for GPIO R1 to port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    //enable alernate functions on port PB3
    GPIO_PORTB_AFSEL_R |= BIT3;

    //enable timer on port B pins 3
    GPIO_PORTB_PCTL_R |= 0x7000;

    //set pin 3 to digital
    GPIO_PORTB_DEN_R |= BIT3;


    //set port 3 to output
    GPIO_PORTB_DIR_R |= 0x08;


}

void TIMER3B_Handler(void){
    //clears interrupt flag
    TIMER3_ICR_R = TIMER_ICR_CBECINT;
    //set times and states
    if(state == LOW){//get rising edge
        rising_edge_time = TIMER3_TBR_R;
        state = HIGH;
    }
    else if(HIGH){//get falling edge
        falling_edge_time = TIMER3_TBR_R;
        state = DONE;
    }
}

void TIMER_INITSONAR(void){
    //Enable Timer3
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;

    //Disable timer (clear bit TnEN in GPTMCTL)
    TIMER3_CTL_R &= ~TIMER_CTL_TBEN;

    //set timer 3B event mode to Both edge trigger interrupt
    TIMER3_CTL_R |= 0x0C00;

    //set configuration to 2 timers
    TIMER3_CFG_R = 0x4;

    //Set to capture mode
    TIMER3_TBMR_R |= 0x003;

    //set to edge-time mode
    TIMER3_TBMR_R |= 0x4;

    //set to count up
    TIMER3_TBMR_R |= 0b10000;




    //set Max upper Bounds
    TIMER3_TBPR_R = 0xFF;
    TIMER3_TBILR_R = 0xFFFF;


    //clear interrupt flag
    TIMER3_ICR_R &= 0x400;

    //enable capture interrupts
    TIMER3_IMR_R |= 0x400;

    //NVIC setup for timerB

    //Priority setup
    NVIC_PRI9_R |= 0x20;

    //enable NVIC interrupts for T3
    NVIC_EN1_R |= 0x10;

    //Bind timer 3B interrupts with the created interrupt handler
    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    //enable global interrupts
    IntMasterEnable();

    //enable timer 3B after changing settings
    TIMER3_CTL_R |= 0x0100;
}


void send_pulse(void){
    //disable alernate functions on port PB3
    GPIO_PORTB_AFSEL_R &= ~BIT3;
    //Disable timer (clear bit TnEN in GPTMCTL)
    TIMER3_CTL_R &= ~TIMER_CTL_TBEN;
    //change PB3 to output
    GPIO_PORTB_DIR_R |= 0x08;
    //set PB3 to high
    GPIO_PORTB_DATA_R |= 0x08;

    //wait 5 microseconds
    timer_waitMicros(5);
    //set  PB3 to low
    GPIO_PORTB_DATA_R &= 0xF7;
    //set PB3 to input
    GPIO_PORTB_DIR_R &= 0xF7;

    //enable alernate functions on port PB3
    GPIO_PORTB_AFSEL_R |= BIT3;
    //enable timer (clear bit TnEN in GPTMCTL)
    TIMER3_CTL_R |= TIMER_CTL_TBEN;
    state = LOW;

}

unsigned int ping_read(void){
    send_pulse();
    while(state != DONE){
        //Wait while receiving
    }
    //find diff
    uint32_t overflow = (falling_edge_time < rising_edge_time);
    if(overflow){
        overflows++;
    }
    unsigned long diff = ((unsigned long)overflow <<24) + falling_edge_time - rising_edge_time;

    unsigned int cm = ((diff * (6.25 * pow(10,-8)))/2) * 34000;

    return cm;

}






