#include <Arduino.h>
#include <uRTCLib.h>
#include <LiquidCrystal.h>

// UART Print registers
 #define RDA 0x80
 #define TBE 0x20  
volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;

// ADC Registers
volatile unsigned char* my_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* my_ADC_DATA = (unsigned int*) 0x78;

// Define PORT B Registers
volatile unsigned char *PORT_B = (unsigned char *) 0x25;
volatile unsigned char *DDR_B =  (unsigned char *) 0x24;
volatile unsigned char *PIN_B =  (unsigned char *) 0x23;

// Define PORT C Registers
volatile unsigned char *PORT_C = (unsigned char *) 0x28;
volatile unsigned char *DDR_C = (unsigned char *) 0x27;
volatile unsigned char *PIN_C = (unsigned char *) 0x26;

// Define PORT D Registers
volatile unsigned char *PORT_D = (unsigned char *) 0x2B;
volatile unsigned char *DDR_D = (unsigned char *) 0x2A;
volatile unsigned char *PIN_D = (unsigned char *) 0x29;

// Define PORT H Registers
volatile unsigned char *PORT_H = (unsigned char *) 0x102;
volatile unsigned char *DDR_H = (unsigned char *)  0x101;
volatile unsigned char *PIN_H = (unsigned char *)  0x100;


// Define pins
#define FAN_PIN 30
#define BLUE_LED_PIN 13
#define RED_LED_PIN 12
#define YELLOW_LED_PIN 11
#define GREEN_LED_PIN 10
#define STOP_BTN_PIN 7




// Define LCD pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

// Setup real time clock module
uRTCLib rtc(0x68);
// Date time char array
char dateTimeStr[18];


// Define system states
enum states{RUNNING_STATE, IDLE_STATE, DISABLED_STATE, ERROR_STATE};
enum states currentState;

void setup(){
  // Define LCD COLS, ROWS
  lcd.begin(16, 2);
  lcdPrint(100.0, 100.0);

  // Define RTC module constants and other things
  #ifdef ARDUINO_ARCH_ESP8266
    URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266
  #else
    URTCLIB_WIRE.begin();
  #endif
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  rtc.set(0, 51, 6, 1, 8, 5, 23);

  // Set system state to disabled
  currentState = DISABLED_STATE;

  // Initialize ADC (required to work)
  adc_init();

  // Initialize UART and set baud rate to 9600
  U0init(9600);

  // Set digital pin 30 (PA7) as output for fan
  *DDR_C |= (1 << 7);

  // Set digital pin 7 (PH4) as input, for STOP button
  *DDR_H &= ~(1 << 4);
  // Enable internal pullup on PH4
  *PORT_H |= 0x10;
  // To check if PH4 button is pressed, use:
  // if(*PIN_H & 0x10){}

  // Set LED pins, digital pins D10-D13 (PB4, PB5, PB6, PB7) to output
  *DDR_B |= (1 << 4);
  *DDR_B |= (1 << 5);
  *DDR_B |= (1 << 6);
  *DDR_B |= (1 << 7);
  // To turn LEDS on:
  // *PORT_B |= (1 << 4);
  // To turn LEDS off:
  // *PORT_B &= !(1 << 4);
}

void loop(){
    if(*PIN_H & 0x10){
      *PORT_B |= (1 << 4);
    }
    else{
      *PORT_B &= !(1 << 4);
    }
    // Refresh the RTC
    rtc.refresh();
    // Set new DateTime to global char[]
    // Print time to serial using uartPrintStr(dateTimeStr);
    sprintf(dateTimeStr, "%02d-%02d-%02d %02d:%02d:%02d", rtc.month(), rtc.day(), rtc.year(), rtc.hour(), rtc.minute(), rtc.second());

    
    // get state of system
    if(currentState = 0){
      // turn on blue led
      // turn motor on
      //
      
    }
    else if (currentState == 1){
      
    }
    else if (currentState == 2){
      
    }
    else if (currentState == 3){
      // turn on yellow led
      // don't perform temperatuer or
    }
    if (currentState != 4){
      //get humidity
      // get temp
      // update LCD once per minute
      // if stop button pressed, fan turns off and system goes into disabled state
    }
  // update state if needed

}

// Accepts char[], prints using UART
void uartPrintStr(char toPrint[]){ 
  for (int i = 0; i < strlen(toPrint); i++) {
    U0putchar(toPrint[i]);      // Print each character in the array
  }
  U0putchar('\n');
}

// Set fan state
void setFan(bool state){
  if(state == 1){
    *PORT_C |= (1 << 7);
  }
  else{
    *PORT_C &= ~(1 << 7);
  }
}

// Print temperature and humidity to display
void lcdPrint(float temperature, float humidity){
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("Temp(F): ");
  lcd.print(temperature, 1);
}

// UART Functions
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

// Analog - Digital Converter Functions

void adc_init()
{
  // setup the A register
  *my_ADCSRA |= 0b10000000; // set bit   7 to 1 to enable the ADC
  *my_ADCSRA &= 0b11011111; // clear bit 6 to 0 to disable the ADC trigger mode
  *my_ADCSRA &= 0b11110111; // clear bit 5 to 0 to disable the ADC interrupt
  *my_ADCSRA &= 0b11111000; // clear bit 0-2 to 0 to set prescaler selection to slow reading
  // setup the B register
  *my_ADCSRB &= 0b11110111; // clear bit 3 to 0 to reset the channel and gain bits
  *my_ADCSRB &= 0b11111000; // clear bit 2-0 to 0 to set free running mode
  // setup the MUX Register
  *my_ADMUX  &= 0b01111111; // clear bit 7 to 0 for AVCC analog reference
  *my_ADMUX  |= 0b01000000; // set bit   6 to 1 for AVCC analog reference
  *my_ADMUX  &= 0b11011111; // clear bit 5 to 0 for right adjust result
  *my_ADMUX  &= 0b11100000; // clear bit 4-0 to 0 to reset the channel and gain bits
}
unsigned int adc_read(unsigned char adc_channel_num)
{
  // clear the channel selection bits (MUX 4:0)
  *my_ADMUX  &= 0b11100000;
  // clear the channel selection bits (MUX 5)
  *my_ADCSRB &= 0b11110111;
  // set the channel number
  if(adc_channel_num > 7)
  {
    // set the channel selection bits, but remove the most significant bit (bit 3)
    adc_channel_num -= 8;
    // set MUX bit 5
    *my_ADCSRB |= 0b00001000;
  }
  // set the channel selection bits
  *my_ADMUX  += adc_channel_num;
  // set bit 6 of ADCSRA to 1 to start a conversion
  *my_ADCSRA |= 0x40;
  // wait for the conversion to complete
  while((*my_ADCSRA & 0x40) != 0);
  // return the result in the ADC data register
  return *my_ADC_DATA;
}
