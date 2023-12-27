/*
 * File:   SPI.c
 * Author: mfgho
 *
 * Created on June 29, 2023, 4:23 AM
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define UP RB0
#define Down RB1
#define Send RB2
void SPI_Master_Init();
void SPI_Write(uint8_t);
void main(void) {
    SPI_Master_Init();
    uint8_t Data=0;
    TRISB=0x07;
    TRISD=0;
    PORTD=0;
    while(1){
        if(UP){
            Data++;
            __delay_ms(250);
        }
        if(Down){
            Data--;
            __delay_ms(250);
        }
        if(Send){
            SPI_Write(Data);
            __delay_ms(250);
        }
        PORTD=Data;
    }
    return;
}
void SPI_Master_Init(){
    SSPM0=0;
    SSPM1=0;
    SSPM2=0;
    SSPM3=0;
    SSPEN=1;
    CKP=0;
    CKE=0;
    SMP=0;
    TRISC5=0;
    TRISC4=1;
    TRISC3=0;
}
void SPI_Write(uint8_t Data){
    SSPBUF=Data;
}