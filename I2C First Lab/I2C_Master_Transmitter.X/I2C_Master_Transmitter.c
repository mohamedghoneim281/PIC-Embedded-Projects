/*
 * File:   I2C_Master_Transmitter.c
 * Author: mfgho
 *
 * Created on July 2, 2023, 4:14 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define I2C_BaudRate 100000
void I2C_Master_Init(void);
void I2C_Wait(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_ACK(void);
void I2C_NACK(void);
unsigned char I2C_Write(unsigned char Data);
void main(void) {
    TRISB=0xFF;
    TRISD=0x00;
    PORTD=0x00;
    unsigned char i=1;
    I2C_Master_Init();
    while(1){
        I2C_Start();
        I2C_Write(0x40);
        I2C_Write(i++);
        I2C_Stop();
        __delay_ms(500);
        RD3=~RD3;
    }
    
    return;
}
void I2C_Master_Init(){
    TRISC3=1;
    TRISC4=1;
    SSPCON=0x28;
    SSPCON2=0x00;
    SSPADD=((_XTAL_FREQ/4)/I2C_BaudRate)-1;
}
void I2C_Wait(){
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}
void I2C_Start(){
    I2C_Wait();
    SEN=1;
}
void I2C_Stop(){
    I2C_Wait();
    PEN=1;
}
void I2C_Restart(){
    I2C_Wait();
    RSEN=1;
}
void I2C_ACK(){
    I2C_Wait();
    ACKDT=0;
    ACKEN=1;
}
void I2C_NACK(){
    I2C_Wait();
    ACKDT=1;
    ACKEN=1;
}
unsigned char I2C_Write(unsigned char Data){
    I2C_Wait();
    SSPBUF=Data;
    I2C_Wait();
    return ACKSTAT;
}