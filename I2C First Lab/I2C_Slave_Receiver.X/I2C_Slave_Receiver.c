/*
 * File:   I2C_Slave_Receiver.c
 * Author: mfgho
 *
 * Created on July 2, 2023, 5:46 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
unsigned char RX_Data=0x00;
void I2C_Slave_Init(unsigned char);
void main(void) {
    TRISD=0;
    PORTD=0;
    I2C_Slave_Init(0x40);
    while(1);
    return;
}
void __interrupt() ISR(void){
    if(SSPIF){
        if(!R_nW){
        char DUMMY=SSPBUF;
        CKP=1;//TURN OFF CLOCK STRETCHING
        while(!BF);
        RX_Data=SSPBUF;
        PORTD=RX_Data;
    }
    CKP = 1;
    SSPIF=0;
    }
}
void I2C_Slave_Init(unsigned char Address){
    SSPADD=Address;
    SSPSTAT=0x80;
    SSPCON=0b00110110;
    SSPCON2=0x01;
    TRISC3=1;
    TRISC4=1;
    SSPIE=1;
    PEIE=1;
    GIE=1;
    SSPIF=0;
}