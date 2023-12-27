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
#define DAC_Pins PORTB
void ADC_Init();
uint16_t ADC_Read(uint8_t);
void main(void) {
    ADC_Init();
    TRISB=0;
    DAC_Pins=0;
    uint16_t ADC_BUFF;
    while(1){
        ADC_BUFF=ADC_Read(0)>>2;//divide by 4 to convert 10 bit to 8 bit to display on PORTB 8 pins
        DAC_Pins=ADC_BUFF;
        __delay_ms(1);
    }
    return;
}
void ADC_Init(void){
    ADCON0=0b01000001;
    ADCON1=0b10000000;
}
uint16_t ADC_Read(uint8_t PIN){
    ADCON0 &=0b11000101;
    ADCON0 |=(PIN<<3);
    __delay_us(30);//WAIT FOR S/H
    GO_DONE=1;
    while(GO_DONE);//WAIT FOR QUANTIZING
    return ((ADRESH<<8) + ADRESL);
}
