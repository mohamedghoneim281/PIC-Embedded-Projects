/*
 * File:   IRQ.c
 * Author: mfgho
 *
 * Created on June 24, 2023, 2:30 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void main(void) {
    TRISC1=0;
    TRISC2=0;
    RC1=0;
    RC2=0;
    TRISB0=1;
    INTEDG=1;
    INTE=1;
    GIE=1;
    while(1){
        RC2=1;
        __delay_ms(1000);
        RC2=0;
        __delay_ms(1000);
    }
    return;
}
void __interrupt()ISR(void){
    if(INTF){
        RC1=~RC1;
        INTF=0;
    }
}