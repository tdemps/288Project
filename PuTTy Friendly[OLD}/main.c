#include <init.h>
#include <communication.h>
#include <movement.h>
#include "lcd.h"
#include <open_interface.h>
#include <stdbool.h>
#include "uart.h" 
#include "wifi.h"
#include "servo.h" //Servo
#include <string.h>
#include <pulse.h>//pulse sensor
#include <ir.h>	//ir sensor
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include <entertainment.h>

int main(void){

    initAll();
    timer_waitMillis(500);

	char input = 0;

	oi_t *sensor = oi_alloc();
	oi_init(sensor);
	init_Songs();

	uart_sendStr("Setup complete \n");

	lcd_printf("Entering main");
	while(1){
	input = comCheck(sensor);   //waits for input from driver, takes action within comCheck

	if(input == '7'){   //finishing sequence
		
		flash_leds();
		playSong(0);
		break;
	}
	
	}
	return 0;
}
