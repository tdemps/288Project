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
#include "WiFi.h"
#include "String.h"

  
/**
 * This method enables the required pins for UART1 functionality.
 * @author Tanner Dempsay
 * @date 4/16/2018
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

/**
 * This method sends a single character over uart.
 * @author Tanner Dempsay
 * @param data  The character to be sent 
 * @date 4/16/2018
 * 
 */
void uart_sendChar(char data){

    while(UART1_FR_R & 0x20){

    }
    UART1_DR_R = data;
}

/**
 * This method waits to receive a single character over uart.
 * @author Tanner Dempsay
 * @date 4/16/2018
 * 
 */
int uart_receive(void){
    char data = 0;

    while(UART1_FR_R & UART_FR_RXFE){
//        if(button_getButton() > 0)
//            return 0;
    }
    data = (char) (UART1_DR_R & 0xFF);
    return data;
}

/**
 * This method sends a string of chars over the uart.
 * @author Tanner Dempsay
 * @param char *data  String of chars to transmit
 * @date 4/16/2018
 */
void uart_sendStr(const char *data){

    int i,j;
    j = 0;
    while(j < strlen(data)) {

        uart_sendChar(data[j]);
        j++;

    }



}
//
//int main(void){
//    char str[21];
//    int i = 0;
//    char data = 0;
//    lcd_init();
//   // uart_init();
//    WiFi_start(thePassword);
//    button_init();
//    //char bstr[100];
//    char strprev[101] = " ";\
//
//    while(1==1){
//        char bstr[101] = "";
//        data = uart_receive();
//        int button = button_getButton();
//
//        if(data == '\r' || strlen(str) == 20){
//            if(data == '\r')
//            {
//                uart_sendChar(10);
//            }
//            lcd_printf("");
//            lcd_printf("%.20s", str);
//            int j = 0;
//            while(j < 20){
//                str[j] = '\0';
//                j++;
//            }
//            i = 0;
//        }else if(data != 0){
//           str[i] = data;
//            i++;
//            uart_sendChar(data);
//            lcd_printf(" %d : %c", i , data);
//            data = 0;
//            }
//
//     switch(button){
//         case 1: strncpy(bstr, "idk",100); break;
//         case 2: strncpy(bstr, "send nudes",100); break;
//         case 3: strncpy(bstr, "just button 3",100);break;
//         case 4: strncpy(bstr, "Blue, no green, Ahhhhh!!!!!!!!!!!",100); break;
//         case 5: strncpy(bstr, "No",100);break;
//         case 6: strncpy(bstr, "Yes",100); break;
//         default: break;
//     }
//     if(strlen(bstr) >= 2 && !(strcmp(strprev, bstr) == 0) ){
//         int j = 0;
//         for(j = 0; j < strlen(bstr); j++){
//             uart_sendChar(bstr[j]);
//         }
//         uart_sendChar(10);
//         strncpy(strprev, bstr,100);
//         timer_waitMillis(500);
//     }
//
//     }
//    }
