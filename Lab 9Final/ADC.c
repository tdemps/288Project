#include "lcd.h"
#include "Timer.h"
#include "Math.h"

void ADC_init(void){

    //GPIO config
    //enable port B clock
    SYSCTL_RCGCGPIO_R |= 0b10;

    //enable clock for ADC port B
    SYSCTL_RCGCADC_R |= 0x1;

    //enable port B pin4 for alternate functions
    GPIO_PORTB_AFSEL_R |= 0x10;

    //set pin 4 to input
    GPIO_PORTB_DEN_R &= 0b11101111;

    //disable analog isolation for PB4
    GPIO_PORTB_AMSEL_R |= 0x10;

    //set up port trigger source as processor default
    GPIO_PORTB_ADCCTL_R = 0x00;


    //ADC config
    //disable SS1 sampler to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN1;

    //initialize ADC source as processor default
    ADC0_EMUX_R = ADC_EMUX_EM1_PROCESSOR;

    //set first sample to use AIN10 pin
    ADC0_SSMUX1_R |= 0x000A;

    //enable raw interrupt status
    ADC0_SSCTL1_R |= (ADC_SSCTL1_IE0 | ADC_SSCTL1_END0);

    //enable oversampling to average
    ADC0_SAC_R |= ADC_SAC_AVG_64X;

    //re enable ADC0 SS1
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN1;
}

double ADC_read(void){
    //initiate SS1 conversion
    int i, final;
    int sum =0;
    for(i = 0; i < 16; i++){
    ADC0_PSSI_R = ADC_PSSI_SS1;

    //wait for ADC Conversion to be complete
    while((ADC0_RIS_R & ADC_RIS_INR1) == 0){
        //wait
    }


    //get result and add
    sum += ADC0_SSFIFO1_R;

    ADC0_ISC_R = ADC_ISC_IN1;
    }


   final = sum/16;

   double cm = 103264 * (pow(final, -1.166));

   return cm;
}


