/*
 * File:   UART_Receiver.c
 * Author: YourName
 *
 * Created on June 26, 2023, 11:27 PM
 */

#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000

void UART_RX_Init(void);
uint8_t UART_Read(void);

uint8_t UART_Buffer = 0;

void main(void) {
    UART_RX_Init();
    
    TRISB = 0; // Set PORTB as output
    PORTB=0;
    while (1) {
        // Code execution continues here
        // You can add your main logic here
    }
    
    return;
}

void UART_RX_Init(void) {
    BRGH = 1;
    SPBRG = 25;
    SYNC = 0;
    SPEN = 1;
    TRISC6 = 1;
    TRISC7 = 1;
    RCIE = 1;
    PEIE = 1;
    GIE = 1;
    CREN = 1;
}

void __interrupt() ISR(void) {
    if (RCIF == 1) {
        UART_Buffer = RCREG; // Read received data
        PORTB = UART_Buffer; // Display received data on PORTB
        
        RCIF = 0; // Clear the receive interrupt flag
    }
}
