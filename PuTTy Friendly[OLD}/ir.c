
#include <ir.h>

void ADC_init(){
    SYSCTL_RCGCGPIO_R |= 2;
    SYSCTL_RCGCADC_R |= 1;
    GPIO_PORTB_AFSEL_R |= 16;
    GPIO_PORTB_DEN_R &= ~16;
    GPIO_PORTB_AMSEL_R |= 16;
    GPIO_PORTB_ADCCTL_R = 0;

    //disable SS0 sample sequencer to configure it
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
    //initialize the ADC trigger source as processor (default)
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;
    //set 1st sample to use the AIN10 ADC pin
    ADC0_SSMUX0_R |= 0x000A;
    //enable raw interrupt status
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);
    //enable oversampling to average
    ADC0_SAC_R |= ADC_SAC_AVG_64X;
    //re-enable ADC0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
    //ADC0_PSSI_R = ADC_PSSI_SS1;
}


unsigned ADC_read(){
    //initiate SS1 conversion
    ADC0_PSSI_R=ADC_PSSI_SS0;
    //wait for ADC conversion to be complete
    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){
        //wait for signal
        }
    //grab result
    ADC0_ISC_R=ADC_ISC_IN0;
    int value = ADC0_SSFIFO0_R;
    return value;
}

int ir_getDist(){
	
    int i = 0, average = 0;

        for(i = 0; i < 20; i++){

        average += ADC_read();
        //lcd_printf("%lu", ADC_read());//smooth raw value by averaging n values
        timer_waitMicros(500);
        }

        average = average / 20;

        return  (69.369 * exp( average *-0.0014 )); //convert to cm using trend line on excel (exponential)

}
