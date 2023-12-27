/*
 * File:   LEDB.c
 * Author: mfgho
 *
 * Created on June 20, 2023, 2:10 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void main(void) {
    TRISBbits.TRISB0=0;
    TRISBbits.TRISB1=0;
    PORTBbits.RB0=0;
    while(1){
       
            PORTBbits.RB0=1;
            __delay_ms(1000);
            PORTBbits.RB0=0;
            __delay_ms(1000);
        
    }
    return;
}
