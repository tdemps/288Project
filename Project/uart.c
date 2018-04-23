/** 
 *@file uart.c
 *@brief this file contains the setup and functions
 *for sending/receiving data over UART1.
 *
 *@author Tanner Dempsay
 *
 *@date 4/16/2018
 */

#include "uart.h"

///setup UART1 for putty communication.
/**
 * This method enables the required pins for UART1 functionality.
 * 8 data bits, one stop, no parity or fifo.
 *
 */
void uart_init(void){
    //enable clock to GPIO, R1 = port B
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //enable clock to UART1, R1 = UART1. ***Must be done before setting Rx and Tx(See DataSheet)
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
    //enable alternate functions on port b pins 0 and 1
    GPIO_PORTB_AFSEL_R |= (BIT0 | BIT1);
    //enable Rx and Txon port B on pins 0 and 1
    GPIO_PORTB_PCTL_R |= 0x00000011;
    //set pin 0 and 1 to digital
    GPIO_PORTB_DEN_R |= (BIT0 | BIT1);
    //set pin 0 to Rx or input
    GPIO_PORTB_DIR_R &= ~BIT0;
    //set pin 1 to Txor output
    GPIO_PORTB_DIR_R |= BIT1;
    //calculate baudrate
    uint16_t iBRD= 8;
    uint16_t fBRD= 44;
      UART1_CTL_R &= ~(UART_CTL_UARTEN);
    //set baud rate
    UART1_IBRD_R = iBRD;UART1_FBRD_R = fBRD;
    //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
    UART1_LCRH_R = UART_LCRH_WLEN_8 ;//use system clock as source
    UART1_CC_R = UART_CC_CS_SYSCLK;
    //re-enable enable RX, TX, and uart
    UART1_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
}
///sends char to putty
/**
 * This method sends a single character over uart.
 * @author Tanner Dempsay
 * @param data The character to be sent 
 */
void uart_sendChar(char data){

    while(UART1_FR_R & 0x20){

    }
    UART1_DR_R = data;
}
///receives a single char
/**
 * This method waits to receive a single char over uart.
 */
int uart_receive(void){
    char data = 0;
    
    while(UART1_FR_R & UART_FR_RXFE){
      //waiting
    }
    data = (char) (UART1_DR_R & 0xFF);
    return data;
}
///sends string to putty
/**
 * This method sends a string of chars over the UART.
 * @author Tanner Dempsay
 * @param char *data  String of chars to transmit.
 */
void uart_sendStr(const char *data){

    int j;
    j = 0;
    while(j < strlen(data)) {

        uart_sendChar(data[j]);
        j++;

    }
}
