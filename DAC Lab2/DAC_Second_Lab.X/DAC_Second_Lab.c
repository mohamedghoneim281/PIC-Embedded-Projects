/*
 * File:   R-2R_Ladder_DAC.c
 * Author: mfgho
 *
 * Created on July 4, 2023, 1:37 PM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000

void main(void) {
    TRISB=0;
    while(1){
        PORTB=0;
        __delay_ms(5000);
        PORTB=51;
        __delay_ms(5000);
        PORTB=103;
        __delay_ms(5000);
        PORTB=154;
        __delay_ms(5000);
        PORTB=205;
        __delay_ms(5000);
        PORTB=0xFF;
        __delay_ms(5000);
    }
    return;
}