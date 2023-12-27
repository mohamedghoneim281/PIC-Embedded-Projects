/*
 * File:   UltraSonic_Sensor.c
 * Author: mfgho
 *
 * Created on June 23, 2023, 6:59 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
float calc_dist(void);
void main(void) {
    unsigned char dist=0;
    TRISB=0;
    PORTB=0;
    TRISC2=0;
    TRISC3=1;
    T1CKPS0=0;
    T1CKPS1=0;
    TMR1CS=0;
    while(1){
        dist=calc_dist()/5;
        switch(dist){
            case 1:
                PORTB=0x01;
                break;
            case 2:
                PORTB=0x03;
                break;
            case 3:
                PORTB=0x07;
                break;
            case 4:
                PORTB=0x0F;
                break;
            default:
                PORTB=0x00;
        }
        __delay_ms(100);
    }
    return;
}
float calc_dist(void){
    float distance;
    TMR1=0;
    RC2=1;
    __delay_us(10);
    RC2=0;
    while(!RC3);
    TMR1ON=1;
    while(RC3);
    distance=TMR1/58.8;
    return distance;
}