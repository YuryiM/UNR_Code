#include <Keypad.h>
#include <SevSeg.h>

#define ROWS 4
#define COLS 4

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// keypad rows
byte colPins[ROWS] = {5, 4, 3, 2};

// keypad columns
byte rowPins[COLS] = {9,8,7,6}; 

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
SevSeg sevseg; 

unsigned short numKey = 0;
unsigned short count = 0;
unsigned long milli = 0;

void setup()
{
  // set num digits on display
  byte numDigits = 4; 
  // digit displays (1,2,3,4)  
  byte digitPins[] = {22, 23, 24, 25}; 
  // segments (a,b,c,d,e,f,g,".")
  byte segmentPins[] = {46, 47, 48, 49, 50, 51, 52, 53}; 

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(10);
}

void loop()
{
  // get key from keypad
  char key = keypad.getKey();

  // update display if: key pressed and not reached max number of digits
  if(!milli && key && numKey <= 999){
    count++;
    numKey = (numKey * 10) + (int(key) - 48);
    
    if(count == 4){
      // set value of milli var to milliseconds that have passed since program beginning
      milli = millis();
      count = 0;
    }
  }
  // if 2 sec have passed since max digits reached, then reset
  else if((millis() - milli) == 2000){
    numKey = 0;
    milli = 0;
  }
  
  sevseg.setNumber(numKey, 0);
  sevseg.refreshDisplay(); 
}
