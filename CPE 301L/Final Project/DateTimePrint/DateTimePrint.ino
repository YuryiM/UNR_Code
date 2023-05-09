//
// Program to echo serial input characters from
// Putty keyboard back to Putty display.
// This version uses proper pointers.
//
//Written by D. Egbert, Version 1.5, 04/03/2017
//              Shawn Ray, Version 1.6 6/19/2022
//
#include "Arduino.h"
#include "uRTCLib.h"


// uRTCLib rtc;
uRTCLib rtc(0x68);
char dateTimeStr[18];
 #define RDA 0x80
 #define TBE 0x20  
 volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
 volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
 volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
 volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
 volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;
//
// main()
//


void setup()
{
  delay (500);
//  Serial.begin(9600);
//  Serial.println("Serial OK");

  #ifdef ARDUINO_ARCH_ESP8266
    URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266
  #else
    URTCLIB_WIRE.begin();
  #endif

  rtc.set(0, 51, 6, 1, 8, 5, 23);
 // initialize the serial port on USART0:
 U0init(9600);
// Serial.begin(9600);
}
void loop()
{
  rtc.refresh();
  sprintf(dateTimeStr, "%02d-%02d-%02d %02d:%02d:%02d", rtc.month(), rtc.day(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());
//  char test[] = rtc.year();
  uartPrintStr(dateTimeStr);
//  U0putchar('\n');     // echo character  
  delay(500);
}

void uartPrintStr(char toPrint[]){ 
  for (int i = 0; i < strlen(toPrint); i++) {
    U0putchar(toPrint[i]);      // Print each character in the array
  }
//  Serial.print(rtc.year());
//  Serial.print('/');
//  Serial.print(rtc.month());
//  Serial.print('/');
//  Serial.print(rtc.day());
//
//  Serial.print(' ');
//
//  Serial.print(rtc.hour());
//  Serial.print(':');
//  Serial.print(rtc.minute());
//  Serial.print(':');
//  Serial.print(rtc.second());

  Serial.println();
}

//
// function to initialize USART0 to "int" Baud, 8 data bits,
// no parity, and one stop bit. Assume FCPU = 16MHz.
//
void U0init(unsigned long U0baud)
{
//  Students are responsible for understanding
//  this initialization code for the ATmega2560 USART0
//  and will be expected to be able to intialize
//  the USART in differrent modes.
//
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 // Same as (FCPU / (16 * U0baud)) - 1;
 *myUCSR0A = 0x20;
 *myUCSR0B = 0x18;
 *myUCSR0C = 0x06;
 *myUBRR0  = tbaud;
}
//
// Read USART0 RDA status bit and return non-zero true if set
//
unsigned char U0kbhit()
{

  return *myUCSR0A & RDA;
}
//
// Read input character from USART0 input buffer
//
unsigned char U0getchar()
{
  return *myUDR0;
}
//
// Wait for USART0 TBE to be set then write character to
// transmit buffer
//
void U0putchar(unsigned char U0pdata)
{
  while((*myUCSR0A & TBE) == 0){}
  *myUDR0 = U0pdata;
  
}
