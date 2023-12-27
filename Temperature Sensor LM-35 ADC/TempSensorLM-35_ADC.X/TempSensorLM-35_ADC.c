/*
 * File:   TempSensorLM-35_ADC.c
 * Author: mfgho
 *
 * Created on June 29, 2023, 8:14 PM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define _XTAL_FREQ 4000000
#define Baud 9600
uint16_t ANORES=0;
float Temperature, Voltage;
char* TempSTR[25];
void ADC_Init();
uint16_t ADC_Read(uint8_t);
void UART_TX_Init(void);
void UART_Write(uint8_t);
void UART_Write_String(char *);
void main(void) {
    UART_TX_Init();
    ADC_Init();
    while(1){
       ANORES= ADC_Read(0);
        Voltage=ANORES*0.0048828;
        Temperature=Voltage/0.01;
        sprintf(TempSTR, "Temperature is -> %.3f c \r \n", Temperature);
        UART_Write_String(TempSTR);
        __delay_ms(10);
    }
    return;
}
void ADC_Init(){
    ADCON0=0b01000001;
    ADCON1=0b10000000;
}
uint16_t ADC_Read(uint8_t ANC){
    if(ANC<0 || ANC>7){
        return 0;
    }
    ADCON0 &= 0b11000101;
    ADCON0 |= ANC << 3;
    __delay_us(30);
    GO_DONE=1;
    while(GO_DONE);
    return ((ADRESH<<8)+ADRESL);
}
void UART_TX_Init(){
    BRGH=1;
    SPBRG=25;//FROM THE DATA SHEET PAGE 116
    SYNC=0;
    SPEN=1;
    TRISC6=1;
    TRISC7=1;
    TXEN=1;
}
void UART_Write(uint8_t data){
    while(!TRMT);
    TXREG=data;
}
void UART_Write_String(char *text){
    for(uint16_t i=0;text[i]!='\0';i++){
        UART_Write(text[i]);
    }
}