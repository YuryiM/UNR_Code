// Port B Addresses
volatile unsigned char* port_b = (unsigned char*) 0x25; 
volatile unsigned char* ddr_b  = (unsigned char*) 0x24; 
volatile unsigned char* pin_b  = (unsigned char*) 0x23;

// Timer setup
volatile unsigned char *myTCCR1A = (unsigned char *) 0x80;
volatile unsigned char *myTCCR1B = (unsigned char *) 0x81;
volatile unsigned char *myTCCR1C = (unsigned char *) 0x82;
volatile unsigned char *myTIMSK1 = (unsigned char *) 0x6F;
volatile unsigned int  *myTCNT1  = (unsigned  int *) 0x84;
volatile unsigned char *myTIFR1 =  (unsigned char *) 0x36;

// Notes played
unsigned int frequency = 0;

void setup() {
  // Initialize serial 
  Serial.begin(9600);
  
  // Set PB6 to OUTPUT
  *ddr_b |= (0x01 << 6);
}

void playTone(int freq){
  *port_b |= (0x01 << 6);
  my_delay(freq);
  *port_b &= ~(0x01 << 6);
  my_delay(freq);
}

void loop() {
  if(frequency){
    playTone(frequency);
  }
  if(Serial.available()){
//    Read in the character
      unsigned char in_char = Serial.read();
     // Write the character back to the Serial Port
     Serial.write(in_char);
     
     if(in_char == 'a' || in_char == 'A'){
        frequency = 440;        
      }
      else if(in_char == 'b' || in_char == 'B'){
        frequency = 494; 
      }
      else if(in_char == 'c' || in_char == 'C'){
        frequency = 523; 
      }
      else if(in_char == 'd' || in_char == 'D'){
        frequency = 587; 
      }
      else if(in_char == 'e' || in_char == 'E'){
        frequency = 659; 
     }
      else if(in_char == 'f' || in_char == 'F'){
       frequency = 698; 
      }
      else if(in_char == 'g' || in_char == 'G'){
       frequency = 784; 
      }
      else if(in_char == 'q' || in_char == 'Q'){
        frequency = 0;
      }
  }
}

void my_delay(unsigned int freq)
{
  // calc period
  double period = 1.0/double(freq);
  // 50% duty cycle
  double half_period = period/ 2.0f;
  // clock period def
  double clk_period = 0.0000000625;
  // calc ticks
  unsigned int ticks = half_period / clk_period;
  // stop the timer
  *myTCCR1B &= 0xF8;
  // set the counts
  *myTCNT1 = (unsigned int) (65536 - ticks);
  // start the timer
  * myTCCR1B |= 0b00000001;
  // wait for overflow
  while((*myTIFR1 & 0x01)==0); // 0b 0000 0000
  // stop the timer
  *myTCCR1B &= 0xF8;   // 0b 0000 0000
  // reset TOV           
  *myTIFR1 |= 0x01;
}
