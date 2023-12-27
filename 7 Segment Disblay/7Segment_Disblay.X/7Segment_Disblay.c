/*
 * File:   7Segment_Disblay.c
 * Author: mfgho
 *
 * Created on June 20, 2023, 4:11 PM
 */


#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define _XTAL_FREQ 4000000
void main(void) {
    unsigned char segment[10] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};

    TRISB=0X00;
    PORTB=0x00;
    while(1){
       uint8_t counter=0;
       for(counter=0;counter<(sizeof(segment)/sizeof(segment[0]));counter++){
           PORTB=segment[counter];
           __delay_ms(1000);
       }    
    }
    return;
}
