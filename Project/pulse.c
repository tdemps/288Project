/** 
 *@file pulse.c
 *@brief this file allows for initializing and 
 *send pulses and get distance via the pulse sensor.
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
 */
#include "lcd.h"
#include "String.h"
#include "Timer.h"
#include "stdlib.h"
#include <stdbool.h>
#include "C:/ti/TivaWare_C_Series-2.1.2.111/driverlib/interrupt.h"

volatile unsigned long last_time = 0, curr_time = 0;
volatile int update_flag = 0;

/**
 * This method is the ISR for timer3B, captures edge times of pulses.
 * @author Tanner Dempsay
 * @date 4/16/2018
 */
void TIMER3B_Handler(void){

    if((TIMER3_MIS_R & TIMER_MIS_CBEMIS) != 0){ //checks interrupt flags
    last_time = curr_time;  //keeps current and last recorded time
    curr_time= TIMER3_TBR_R;
    update_flag += 1;       //updates state
    }
   TIMER3_ICR_R |= TIMER_ICR_CBECINT; // 0x400;  //clears interrupt flag

}
/**
 * Initializes pin B3 and timer3B for use with pulse sensor.
 * @author Tanner Dempsay
 * @date 4/16/2018
 */
 void pulse_init(void){
      SYSCTL_RCGCGPIO_R |= 2;
      GPIO_PORTB_AFSEL_R |= 0x08;
      GPIO_PORTB_DEN_R |= 8;
      GPIO_PORTB_PCTL_R |= 0x7000;
      GPIO_PORTB_DIR_R &= ~0x08;
      SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;

     TIMER3_CTL_R &= ~0x100;
     TIMER3_CFG_R |= TIMER_CFG_16_BIT;
     TIMER3_TBMR_R |= 0x17;
     TIMER3_CTL_R |= 0xC00;
     TIMER3_TBPR_R = 0xFF;    //good
     TIMER3_TBILR_R = 0xFFFF; //good
     TIMER3_IMR_R |= 0x400; // CBEIM = bit 10, 0b100_0000_0000
     TIMER3_ICR_R |= 0x400; // CBECINT = bit 10, 0b100_0000_0000

     NVIC_PRI9_R |= 0x20;   //good
     NVIC_EN1_R |= 0x10;    //good

     IntRegister(INT_TIMER3B, TIMER3B_Handler);
     IntMasterEnable();
     TIMER3_CTL_R |= TIMER_CTL_TBEN;
 }

/**
 * Sends an output high signal to initialize a distance reading.
 * @author Tanner Dempsay
 * @date 4/16/2018
 */
 
void send_pulse(void){
    GPIO_PORTB_AFSEL_R &= ~8;
    GPIO_PORTB_DIR_R |= 0x08;// set PB3 as output
    GPIO_PORTB_DATA_R |= 0x08;// set PB3 to high
    timer_waitMicros(10);
    // wait at least 5 microseconds based on data sheet
    GPIO_PORTB_DATA_R &= 0xF7; // set PB3 to low
    GPIO_PORTB_DIR_R &= 0xF7;// set PB3 as input
    GPIO_PORTB_AFSEL_R |= 8;

}
/**
 * Returns the distance calculated by the pulse sensor
 * in cm.
 * @author Tanner Dempsay
 * @date 4/16/2018
 */
unsigned long pulse_getDist(void){
	
    unsigned long time_diff = 0;
    unsigned overflow = 0;
    unsigned long cm = 0;

  //pulse_init();
  send_pulse();
  while(1){

    if(update_flag == 4){       //waits until pulse is received
      time_diff = curr_time - last_time;
      cm =  (time_diff / 1600) * 3.40 / 2;  //convert clock count to distance
      //lcd_printf(" clk count: %lu \n cm: %lu \n overflow: %lu",  time_diff, cm, overflow);

      //timer_waitMillis(500);
      update_flag = 0;      //clear flag used by ISR
      if(curr_time < last_time)
          time_diff = ((unsigned long) overflow << 24) + curr_time-last_time;   //use overflow to correct time diff
      overflow += (curr_time < last_time);
	  return cm;
      }

  }
}



