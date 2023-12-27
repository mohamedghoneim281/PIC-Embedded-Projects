/*
 * File:   UART_Reciever.c
 * Author: mfgho
 *
 * Created on June 26, 2023, 11:27 PM
 */

 
#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
//--------------------------------
// IO Pins Defines (Mappings)
#define UP RB0
#define Down RB1
#define Send RB2
//--------------------------------
// Functions Declarations
void UART_TX_Init(void);
void UART_Write(uint8_t);
//--------------------------------
// Main Routine
void main(void)
{
  //--[ Peripherals & IO Configurations ]--
  UART_TX_Init(); // Initialize The UART in Master Mode @ 9600bps
  uint8_t Data = 0; // The Data Byte
  TRISB = 0x07; // RB0, RB1 & RB2 Are Input Pins (Push Buttons)
  TRISD = 0x00; // Output Port (4-Pins)
  PORTD = 0x00; // Initially OFF
  //---------------------------
  while(1)
  {
    if (UP) // Increment The Data Value
    {
      Data++;
      __delay_ms(250);
    }
    if (Down) // Decrement The Data Value
    {
      Data--;
      __delay_ms(250);
    }
    if (Send) // Send The Current Data Value Via UART
    {
      UART_Write(Data);
      __delay_ms(250);
    }
    PORTD = Data; // Display The Current Data Value @ PORTD
  }
  return;
}
//--------------------------------
// Functions Definitions
 
void UART_TX_Init(void)
{
  BRGH = 1;   // Set For High-Speed Baud Rate
  SPBRG = 25; // Set The Baud Rate To Be 9600 bps
  //--[ Enable The Ascynchronous Serial Port ]--
  SYNC = 0;
  SPEN = 1;
  //--[ Set The RX-TX Pins to be in UART mode (not io) ]--
  TRISC6 = 1;  // As stated in the datasheet
  TRISC7 = 1;  // As stated in the datasheet
  TXEN = 1; // Enable UART Transmission
}
 
void UART_Write(uint8_t data)
{
  while(!TRMT);
  TXREG = data;
}