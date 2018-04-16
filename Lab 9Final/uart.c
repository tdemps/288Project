/**
*
* 	@file  uart.c
*
*
*
*
*
*   @author
*   @date
*/

#include "uart.h"
#include "lcd.h"
#include "button.h"
#include "WiFi.h"

/**
 * @brief sets all necessary registers to enable the uart 1 module.
 */
void uart_init(void){
    int baudRate = 115200;
    //enable clock for GPIO R1 to port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

	//enable clock to uart 1
	SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;

	//enable alernate functions
	GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);

	//enable Rx and Tx on port B pins 0 and 1
	GPIO_PORTB_PCTL_R |= 0x00000011;

	//set pin 0 and 1 to digital
	GPIO_PORTB_DEN_R |= (BIT0 | BIT1);

	//set pin 0 to Rx
	GPIO_PORTB_DIR_R &= ~BIT0;

	//set pin 1 to Tx or output
	GPIO_PORTB_DIR_R |= BIT1;

	//calculate baudrate
	uint16_t iBRD = 8;
	uint16_t fBRD = 44;

	//turn off uart
	UART1_CTL_R &= ~(UART_CTL_UARTEN);

	//set baud rate
	UART1_IBRD_R = iBRD;
	UART1_FBRD_R = fBRD;

	//set frame
	UART1_LCRH_R = UART_LCRH_WLEN_8;

	//use system clock
	UART1_CC_R = UART_CC_CS_SYSCLK;

	//re-enable Rx,Tx, and uart1
	UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);


	//
}



/**
 * @brief Sends a single 8 bit character over the uart 1 module.
 * @param data the data to be sent out over uart 1
 */
void uart_sendChar(char data){

    //wait till there is room to send data
	while(UART1_FR_R & 0x20){

	}
	//send data
	UART1_DR_R = data;
}

/**
 * @brief polling receive an 8 bit character over uart 1 module.
 * @return the character received or a -1 if error occured
 */
int uart_receive(void){
	char data = 0;
	int lastButton = 0;

	//wait to recieve
	while(UART1_FR_R & UART_FR_RXFE){
	    //switches are flipped
	    if(button_getButton() == 1 && lastButton != 1){
	        uart_sendStr("Yes");
	        lastButton = 1;
	    }
	    if(button_getButton() == 2 && lastButton != 2){
	        uart_sendStr("No");
	        lastButton = 2;
	            }
	    if(button_getButton() == 3 && lastButton != 3){
	        uart_sendStr("Blue, no green, Ahhhhh!!!");
	        lastButton = 3;
	            }
	    if(button_getButton() == 4 && lastButton != 4){
	        uart_sendStr("42");
	        lastButton = 4;
	            }
	    if(button_getButton() == 5 && lastButton != 5){
	        uart_sendStr("Yay I can press buttons");
	        lastButton = 5;
	            }
	    if(button_getButton() == 6 && lastButton != 6){
	        uart_sendStr("Wrong button");
	        lastButton = 6;
	            }
	}
	//mask the error bits and grab only the 8 data bits
	data = (char) (UART1_DR_R & 0xFF);

	return data;
}

/**
 * @brief sends an entire string of character over uart 1 module
 * @param data pointer to the first index of the string to be sent
 */
void uart_sendStr(const char *data){
	int i;
    for(i=0; i < strlen(data); i++){
        uart_sendChar(data[i]);
	}
}



