/*
 * File:   I2C_Slave_Transmitter.c
 * Author: mfgho
 *
 * Created on July 2, 2023, 9:01 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void I2C_Slave_Init(unsigned char);
void main(void) {
    TRISB=0xFF;
    nRBPU=0;/* weak pull-up resistors are enabled for the PORTB pins, which means that if a pin is configured as an input
             *  and left unconnected, the weak pull-up resistor will pull the pin to a logic high (1) level.*/
    I2C_Slave_Init(0x40);
    while(1);
    return;
}
void __interrupt()ISR(void){
    if(SSPIF){
        if(!D_nA && R_nW){
            char Dummy=SSPBUF;
            SSPBUF=PORTB;
            CKP=1;
            while(BF);
        }
        CKP=1;
        SSPIF=0;
    }
}
void I2C_Slave_Init(unsigned char Address)
{
  SSPADD = Address;
  SSPSTAT = 0x80;
  SSPCON = 0x36;
  SSPCON2 = 0x01;
  TRISC3 = 1;
  TRISC4 = 1;
  GIE = 1;
  PEIE = 1;
  SSPIE = 1;
SSPIF = 0;
}