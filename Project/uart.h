/**
*   @file uart.h
*   @brief Used to set up the RS232 connector and WIFI module
*   uses UART1 at 115200
*
*   @author idk
*   @date 04/10/2018
*/

#ifndef UART_H_
#define UART_H_

#include <Timer.h>
#include <WiFi.h>
#include <String.h>
#include <inc/tm4c123gh6pm.h>

/**
 * This method enables the required pins for UART1 functionality.
 *
 */
void uart_init(void);

/**
 * This method sends a single character over uart.
 * @author Tanner Dempsay
 * @param data The character to be sent 
 * 
 */
void uart_sendChar(char data);

/**
 * This method waits to receive a single character over uart.
 *
 */
int uart_receive(void);

/**
 * This method sends a string of chars over the uart.
 * @author Tanner Dempsay
 * @param char *data  String of chars to transmit
 *
 */
void uart_sendStr(const char *data);


#endif /* UART_H_ */
