/*
 * File:   HC-05.c
 * Author: mfgho
 *
 * Created on June 28, 2023, 12:07 AM
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define Blue_LED_ON    49    //ascii 1
#define Blue_LED_OFF   50    //ascii 2
#define Yellow_Toggle  51    //ascii 3
void UART_RX_Init(void);
uint8_t UART_Buffer =0;
void main(void) {
    UART_RX_Init();
    TRISB0=0;
    TRISB1=0;
    RB0=0;
    RB1=0;
    while(1){
        
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
            if(UART_Buffer==Blue_LED_ON){
                RB0=1;
            }
            if(UART_Buffer==Blue_LED_OFF){
                RB0=0;
            }
            if(UART_Buffer==Yellow_Toggle){
                RB1=~RB1;
            }
        RCIF = 0; // Clear the receive interrupt flag
    }
}