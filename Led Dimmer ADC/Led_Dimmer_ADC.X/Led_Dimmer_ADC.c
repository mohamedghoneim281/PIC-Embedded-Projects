/*
 * File:   Led_Dimmer_ADC.c
 * Author: mfgho
 *
 * Created on June 29, 2023, 4:58 PM
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void PWM1_Init();
void PWM1_Set_Duty(uint16_t);
void ADC_Init();
uint16_t ADC_Read(uint8_t);
void main(void) {
    PWM1_Init();
    ADC_Init();
    while(1){
        PWM1_Set_Duty(ADC_Read(0));
        __delay_ms(1);
    }
    return;
}
void PWM1_Init(){
    CCP1M3=1;
    CCP1M2=1;
    TRISC2=0;
    PR2=250;//FREQ~1KHZ WAIT TO KNOW WHY
    T2CKPS0=1;
    T2CKPS1=0;
    TMR2ON=1;
}
void PWM1_Set_Duty(uint16_t DC){
    if(DC<1024){
        CCP1Y=DC & 1;
        CCP1X=DC & 2;
        CCPR1L=DC>>2;
    }
}
void ADC_Init(){
    ADCON0=0b01000001;
    ADCON1=0b10000000;
    
}
uint16_t ADC_Read(uint8_t ANC){
    if(ANC<0 || ANC>7){
        return 0;
    }
    ADCON0&= 0b11000101;
    ADCON0 |= ANC <<3;
    __delay_us(30);//min aquisition time=20uS so that's a good safety factor
    GO_DONE=1;
    while(GO_DONE);
    return ((ADRESH<<8)+ADRESL);
}