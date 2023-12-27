/*
 * File:   SPI_Slave.c
 * Author: mfgho
 *
 * Created on June 29, 2023, 5:05 AM
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
void SPI_Slave_Init();
uint8_t Data;
void main(void) {
    SPI_Slave_Init();
    TRISB=0;
    while(1){
        PORTB=Data;
    }
    return;
}
void SPI_Slave_Init(){
    SSPM0=1;
    SSPM1=0;
    SSPM2=1;
    SSPM3=0;
    SSPEN=1;
    CKP=0;
    CKE=0;
    SMP=0;
    TRISC5=0;
    TRISC4=1;
    TRISC3=1;
    SSPIE=1;
    PEIE=1;
    GIE=1;
}
void __interrupt()ISR(void){
    if(SSPIF){
        Data=SSPBUF;
        SSPIF=0;
    }
}