#include "lcd_stepper.h"
#include "String.h"
#include "button.h"
/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 */
int fuckoff (void) {
	// Initialize the the LCD.  This also clears the screen.

    lcd_init();
    button_init();
    while(1) { // loop indefinitely
        uint8_t button = button_getButton();
        lcd_printf("Button: %d", button);
    }

	return 0;
}
