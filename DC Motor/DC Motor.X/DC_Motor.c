/*
 * File:   DC Motor.c
 * Author: mfgho
 *
 * Created on June 25, 2023, 12:39 AM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000
#define Rev RB0
#define LV0 RB1
#define LV1 RB2
#define LV2 RB3
#define LV3 RB4
void PWM1_Set_Duty(uint16_t);

void main(void) {
    TRISB=0b00011111;
    TRISD0=0;
    TRISD1=0;
    RD0=0;
    RD1=1;
    CCP1M3=1;
    CCP1M2=1;
    TRISC2=0;
    PR2=124;
    T2CKPS0=0;
    T2CKPS1=1;
    TMR2ON=1;
    while(1){
        if(Rev){
            RD0=~RD0;
            RD1=~RD1;
            __delay_ms(500);
            
        }
        if(LV0){
            PWM1_Set_Duty(0);
            __delay_ms(100);
        }
        if(LV1){
            PWM1_Set_Duty(250);
            __delay_ms(100);
    }
        if(LV2){
            PWM1_Set_Duty(375);
            __delay_ms(100);}
        if(LV3){
            PWM1_Set_Duty(500);
            __delay_ms(100);}
        __delay_ms(10);
    }
        return;

}
void PWM1_Set_Duty(uint16_t DC){
    if(DC<1024){
        CCP1X=DC & 2;
        CCP1Y=DC& 1;
        CCPR1L=DC<<2;
    }
}