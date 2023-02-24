// Port K
volatile unsigned char* port_k = (unsigned char*) 0x108; 
volatile unsigned char* ddr_k  = (unsigned char*) 0x107; 
volatile unsigned char* pin_k  = (unsigned char*) 0x106; 

// Port D
volatile unsigned char* port_d = (unsigned char*) 0x2B; 
volatile unsigned char* ddr_d  = (unsigned char*) 0x2A; 
volatile unsigned char* pin_d  = (unsigned char*) 0x29; 

// Port E
volatile unsigned char* port_e = (unsigned char*) 0x2E; 
volatile unsigned char* ddr_e = (unsigned char*) 0x2D; 
volatile unsigned char* pin_e  = (unsigned char*) 0x2C;


void setup() 
{
  // Initialize the Serial Port
  Serial.begin(9600);

  //set PK2 to INPUT
  *ddr_k &= 0xFB;
  // enable pullup resistor on PK2
  *port_k |=  0x04;

  // set PD0 to OUTPUT
  *ddr_d |= 0x01;
  // enable pullup on PD0
  *port_d |=  0xFE;

  //set PE3 to OUTPUT
  *ddr_e |= 0xF7;
  // enable pullup resistor on PE3
  *port_e |=  0x8;
}

void loop() 
{

  // if the pin is high
  if(*pin_k & 0x04)
  {
    *port_d |= 0x01;
    *port_e &= 0x8;
    // WRITE_HIGH_PD(0);
    Serial.println("PIN IS HIGH");
  }
  // if the pin is low
  else
  {
    *port_d &= 0xFE;
    *port_e |= 0xF7;
    Serial.println("PIN IS LOW");
  }
  delay(12);
}
