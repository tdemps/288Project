#include <init.h>

void initAll(){
	lcd_init();

	ADC_init();
	pulse_init();
	//servo_init();
	uart_init();

//	lcd_printf("Setup complete");
	uart_sendStr("Setup complete \n");
	
	return;
}
