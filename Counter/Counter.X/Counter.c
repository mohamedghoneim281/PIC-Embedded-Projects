/*
 * File:   Counter.c
 * Author: mfgho
 *
 * Created on June 24, 2023, 2:15 PM
 */


#include <xc.h>
#include "config.h"
void main(void) {
    TRISB=0;
    PORTB=0;
    TMR1=0;
    TMR1CS=1;
    T1OSCEN=1;
    T1SYNC=0;
    T1CKPS0=0;
    T1CKPS1=0;
    TMR1ON=1;
    while(1){
        PORTB=TMR1;
    }
    return;
}
