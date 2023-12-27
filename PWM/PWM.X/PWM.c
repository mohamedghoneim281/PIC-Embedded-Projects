/*
 * File:   PWM.c
 * Author: mfgho
 *
 * Created on June 24, 2023, 4:38 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void PWM1_Set_Duty(uint16_t);
void main(void) {
    CCP1M3=1;
    CCP1M2=1;
    PR2=124;
    TRISC2=0;
    T2CKPS0=1;
    T2CKPS1=0;
    TMR2ON=1;
    uint16_t DC=0;
    while(1){
        while(DC<500){
            PWM1_Set_Duty(DC);
            DC++;
            __delay_ms(2);
        }
        __delay_ms(100);
        while(DC>0){
            PWM1_Set_Duty(DC);
            DC--;
            __delay_ms(2);
        }
        __delay_ms(100);
    }
    return;
}
void PWM1_Set_Duty(uint16_t DC){
    if(DC<1024){
        CCP1Y= DC & 1;
        CCP1X= DC & 2;
        CCPR1L=DC >> 2;
    }
}