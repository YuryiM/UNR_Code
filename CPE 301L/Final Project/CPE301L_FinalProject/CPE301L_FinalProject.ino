#include <Arduino.h>
#include <uRTCLib.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <Stepper.h>

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

// Define PORT E Registers
volatile unsigned char *PORT_E = (unsigned char *) 0x2E;
volatile unsigned char *DDR_E = (unsigned char *) 0x2D;
volatile unsigned char *PIN_E = (unsigned char *) 0x2C;

// Define PORT H Registers
volatile unsigned char *PORT_H = (unsigned char *) 0x102;
volatile unsigned char *DDR_H = (unsigned char *)  0x101;
volatile unsigned char *PIN_H = (unsigned char *)  0x100;

// Define PORT L Registers
volatile unsigned char *PORT_L = (unsigned char *) 0x10B;
volatile unsigned char *DDR_L = (unsigned char *)  0x10A;
volatile unsigned char *PIN_L = (unsigned char *)  0x109;

// Define LCD pins
LiquidCrystal lcd(9, 8, 5, 4, 3, 7);

// Set up DHT11 Temp/Humidity Sensor
#define DHTPIN 34
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Water level sensor variables
int water_level;
int water_level_threshold = 100;

// Start button state
volatile bool start_pressed = false;

// Define # of steps / revolution for stepper motor
const int stepsPerRev = 2048;

// Creates stepper class instance
// Pin order in function parameters is: IN1 / IN2 / IN3 / IN4
Stepper myStepper = Stepper(stepsPerRev, 29, 27, 25, 23);

int ventPosition = 0;

// Setup real time clock module
uRTCLib rtc(0x68);
// Time char array
char timeStr[10];
int secs_LCD_update;

// Declare temperature and humidity variables
// Temperature measured in degrees Celsius
float temp;
float temp_threshold = 35.0;
float humidity;

// Define system states
enum states{RUNNING_STATE, IDLE_STATE, DISABLED_STATE, ERROR_STATE};
enum states currentState;
// Enum -> String
const char * const states_str[] =
{
    [RUNNING_STATE] = "RUNNING",
    [IDLE_STATE] = "IDLE",
    [DISABLED_STATE]  = "DISABLED",
    [ERROR_STATE]  = "ERROR",
};

void setup(){
  // Initialize DHT11 sensor
  dht.begin();
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
  
  // Define RTC module constants
  #ifdef ARDUINO_ARCH_ESP8266
    URTCLIB_WIRE.begin(0, 2); // D3 and D4 on ESP8266
  #else
    URTCLIB_WIRE.begin();
  #endif
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  rtc.set(0, 51, 6, 1, 8, 5, 23);

  // Set initial seconds time
  secs_LCD_update = rtc.second();

  // Define LCD COLS, ROWS
  lcd.begin(16, 2);
  lcdPrintTemp();

  // Set up interrupt for D2 (PE4) start button
  EICRA |= (1 << ISC01);
  EIMSK |= (1 << INT4);

  // Set initial system state to idle
  currentState = IDLE_STATE;

  // Set the speed to 5 rpm:
  myStepper.setSpeed(5);
  
  // Initialize ADC
  adc_init();

  // Get initial water level
  water_level = adc_read(15);

  // Initialize UART and set baud rate to 9600
  U0init(9600);

  // Set D30 (PC7) as output, for transistor control
  *DDR_C |= (1 << 7);

  // Set D32 (PC5) as output, for water level monitor
  *DDR_C |= (1 << 5);
  
  // Set D2 (PE4) as input, for START button
  *DDR_E &= ~(1 << 4);
  // Enable internal pullup  
  *PORT_E |= 0x10;
    // Set D44 (PL5) as input, for STOP button
  *DDR_L &= ~(1 << 5);
  *PORT_L |= 0x20;
  // Set D42 (PL7) as input, for RESET button
  *DDR_L &= ~(1 << 7);
  *PORT_L |= 0x8;

  // Set LED pins, digital pins D10-D13 (PB4, PB5, PB6, PB7) to output
  *DDR_B |= (1 << 4); // PB4 -- GREEN
  *DDR_B |= (1 << 5); // PB5 -- YELLOW
  *DDR_B |= (1 << 6); // PB6 -- RED
  *DDR_B |= (1 << 7); // PB7 -- BLUE
}

void loop(){
  // Refresh the DS1307 RTC
  rtc.refresh();
  // Set new time to global char[]
  // To print time to serial use: uartPrintStr(timeStr);
  sprintf(timeStr, "%02d:%02d:%02d", rtc.hour(), rtc.minute(), rtc.second());
  
  if (currentState != DISABLED_STATE){
    // Read temperature and humidity
    updateDHT();
    
    // Read vent control potentiometer
    int ventPotent = adc_read(0);

    // Rotate stepper motor based on potentiometer position
    if(ventPotent > 420 && ventPosition < 100){
      myStepper.step(205);
      ventPosition += 10;
      uartPrintVentPos();
    }
    else if(ventPotent < 210 && ventPosition > 0){
      myStepper.step(-205);
      ventPosition -= 10;
      uartPrintVentPos();
    }
    
    // Update LCD once per minute
    if(secs_LCD_update == rtc.second()){ lcdPrintTemp(); }
    
    if(currentState == IDLE_STATE){
      ledOFF();
      // Turn on green led
      *PORT_B |= (1 << 4);
      setFan(0);

      updateWaterLevel();
      // If STOP button pressed, change to disabled state
      if(*PIN_L & 0x20){
        changeState(DISABLED_STATE);
      }
      else if(water_level < water_level_threshold){
        changeState(ERROR_STATE);
      }
      else if(temp > temp_threshold){
        changeState(RUNNING_STATE);
      }
    }
    else if (currentState == ERROR_STATE){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ERROR");
      ledOFF();
      // Turn on red LED
      *PORT_B |= (1 << 6);
      setFan(0);

      // Power off water level monitor
      *PORT_C &= !(1 << 5);

      // if stop pressed
      if(*PIN_L & 0x20){
        changeState(DISABLED_STATE);
      }
      else if(*PIN_L & 0x80){ // if reset pressed
        changeState(IDLE_STATE);
        updateDHT();
        lcd.clear();
        lcdPrintTemp();
      }
    }
    else if (currentState == RUNNING_STATE){
      ledOFF();
      *PORT_B |= (1 << 7);
      setFan(1);

      updateWaterLevel();

      // If STOP button pressed, change to disabled state
      if(*PIN_L & 0x20){
        changeState(DISABLED_STATE);
      }
      else if(water_level < water_level_threshold){
        changeState(ERROR_STATE);
      }
      else if(temp < temp_threshold){
        changeState(IDLE_STATE);
      }
    }
    
  }
  else if(currentState == DISABLED_STATE){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DISABLED");
    ledOFF();
    // Set D11 (PB5) yellow LED ON
    *PORT_B |= (1 << 5);
    setFan(0);

    // Power off water level monitor
    *PORT_C &= !(1 << 5);

    // if start button is pressed, set state to idle
    // start button monitored using ISR() (see below)  
    if(start_pressed){
      changeState(IDLE_STATE);
      updateDHT();
      lcd.clear();
      lcdPrintTemp();
      start_pressed = false;
    }
  }  
}

// Update humidity and temperature from DHT
void updateDHT(){
  humidity = dht.readHumidity();
  temp = dht.readTemperature();
}

// Update water level
void updateWaterLevel(){
  // Set PC5, water level monitor power HIGH
  *PORT_C |= (1 << 5);
  // Read from A15 (PK7)
  water_level = adc_read(15);
}

// Turn all LEDs off
void ledOFF(){
  *PORT_B &= 0b00000000;
}

// Change system state and print using UART
void changeState(enum states newState){
  uartPrintStr(timeStr);
  uartPrintStr(" -- State changed from ");
  uartPrintStr(states_str[currentState]);
  uartPrintStr(" to ");
  uartPrintStr(states_str[newState]);
  U0putchar('\n');

  currentState = newState;
}


// Prints string to UART
void uartPrintStr(char toPrint[]){ 
  for (int i = 0; i < strlen(toPrint); i++) {
    U0putchar(toPrint[i]);      // Print each character in the array
  }
}

// Prints vent position using UART
void uartPrintVentPos(){
  uartPrintStr(timeStr);
  uartPrintStr(" -- Vent position changed to ");
  printDigit(ventPosition);
  uartPrintStr(" % open");
  U0putchar('\n');
}

// Prints number using UART
void printDigit(int N){
    char arr[100];
    int i = 0;
    int j, r;
  
    while (N != 0) {
        r = N % 10;
        arr[i] = r + '0';
        i++;
        N = N / 10;
    }
    for (j = i - 1; j > -1; j--) {
        U0putchar(arr[j]);
    }
}

// Set fan state
// 1 -- ON
// 0 -- OFF
void setFan(bool state){
  if(state == 1){ *PORT_C |= (1 << 7); }
  else{ *PORT_C &= ~(1 << 7); }
}

// Set water level monitor state
// 1 -- ON
// 0 -- OFF
void setWaterSensor(bool state){
  if(state == 1){ *PORT_C |= (1 << 5); }
  else{ *PORT_C &= ~(1 << 5); }
}

// Print temperature and humidity to display
void lcdPrintTemp(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity, 2);
  lcd.print("%");
  
  lcd.setCursor(0, 1);
  lcd.print("Temp(C):  ");
  lcd.print(temp, 2);
}

// ISR() for monitoring PE4 start button
ISR(INT4_vect) {
  start_pressed = true; 
}

// UART Functions
void U0init(unsigned long U0baud)
{
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  *myUCSR0A = 0x20;
  *myUCSR0B = 0x18;
  *myUCSR0C = 0x06;
  *myUBRR0  = tbaud;
}

unsigned char U0kbhit()
{

  return *myUCSR0A & RDA;
}

unsigned char U0getchar()
{
  return *myUDR0;
}

void U0putchar(unsigned char U0pdata)
{
  while((*myUCSR0A & TBE) == 0){}
  *myUDR0 = U0pdata;
  
}

// Analog -> Digital Converter Functions
void adc_init()
{
  // set up the A register
  *my_ADCSRA |= 0b10000000; 
  *my_ADCSRA &= 0b11011111; 
  *my_ADCSRA &= 0b11110111; 
  *my_ADCSRA &= 0b11111000; 
  // set up the B register
  *my_ADCSRB &= 0b11110111; 
  *my_ADCSRB &= 0b11111000; 
  // set up the MUX Register
  *my_ADMUX  &= 0b01111111;
  *my_ADMUX  |= 0b01000000;
  *my_ADMUX  &= 0b11011111;
  *my_ADMUX  &= 0b11100000;
}
unsigned int adc_read(unsigned char adc_channel_num)
{
  *my_ADMUX  &= 0b11100000;
  *my_ADCSRB &= 0b11110111;
  if(adc_channel_num > 7)
  {
    adc_channel_num -= 8;
    *my_ADCSRB |= 0b00001000;
  }
  *my_ADMUX  += adc_channel_num;
  *my_ADCSRA |= 0x40;
  while((*my_ADCSRA & 0x40) != 0);
  return *my_ADC_DATA;
}
