/*
 * File:   EEPROM_Read_Write.c
 * Author: mfgho
 *
 * Created on June 26, 2023, 8:44 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define Read RB0
#define W_3 RB1
#define W_5 RB2
#define W_7 RB3
void EEPROM_Write(uint8_t, uint8_t);
uint8_t EEPROM_Read(uint8_t);
void main(void) {
    TRISB=0x0F;
    TRISD=0;
    PORTD=0;
    uint8_t Address=0;
    while(1){
        if(W_3) 
    {
      EEPROM_Write(Address++, 3);
      __delay_ms(500);
    }
    if(W_5) 
    {
      EEPROM_Write(Address++, 5);
      __delay_ms(500);
    }
    if(W_7) 
    {
      EEPROM_Write(Address++, 7);
      __delay_ms(500);
    }
    if(Address == 3)
      Address = 0;
    if(Read==1){
        for(uint8_t i=0;i<3;i++){
            PORTD=EEPROM_Read(i);
            __delay_ms(1000);
        }
    }
    }
    return;
}
void EEPROM_Write(uint8_t Address, uint8_t Data)
{
  while(EECON1bits.WR); // Waits Until Last Attempt To Write Is Finished
  EEADR = Address;      // Writes The Address To Which We'll Wite Our Data
  EEDATA = Data;        // Write The Data To Be Saved
  EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
  EECON1bits.WREN = 1;  // Enable The Operation !
  INTCONbits.GIE = 0;   // Disable All Interrupts Until Writing Data Is Done
  EECON2 = 0x55;        // Part Of Writing Mechanism..
  EECON2 = 0xAA;        // Part Of Writing Mechanism..
  EECON1bits.WR = 1;    // Part Of Writing Mechanism..
  INTCONbits.GIE = 1;   // Re-Enable Interrupts
  EECON1bits.WREN = 0;  // Disable The Operation
  EECON1bits.WR = 0;    // Ready For Next Writing Operation
}
uint8_t EEPROM_Read(uint8_t Address)
{
  uint8_t Data;
  EEADR = Address;      // Write The Address From Which We Wanna Get Data
  EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
  EECON1bits.RD = 1;    // Start The Read Operation
  Data = EEDATA;        // Read The Data
  return Data;
}