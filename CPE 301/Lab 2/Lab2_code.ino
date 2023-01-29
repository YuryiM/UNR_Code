/****************************************
 * Name: Yuryi Mironchyk
 * Assignment: Lab 2 Decoders
 * Date: 1/29/2023
 ****************************************/

#define LSB_BTN 3
#define MSB_BTN 4

#define LED1_PIN 6
#define LED2_PIN 7
#define LED3_PIN 8
#define LED4_PIN 9

void setup() {
  // put your setup code here, to run once:
  pinMode(LSB_BTN, INPUT);
  pinMode(MSB_BTN, INPUT);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int buttonFirst = digitalRead(LSB_BTN);
  int buttonSecond = digitalRead(MSB_BTN);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW); 

    // DECODER BLOCK
  if(buttonSecond == LOW && buttonFirst == LOW){      // First starts on the right
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW); 
    digitalWrite(LED4_PIN, HIGH); 
    
  }else if(buttonSecond == LOW && buttonFirst == HIGH){
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, HIGH); 
    digitalWrite(LED4_PIN, LOW);
    
  }else if(buttonSecond == HIGH && buttonFirst == LOW){
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, LOW); 
    digitalWrite(LED4_PIN, LOW); 
    
  }else if(buttonSecond == HIGH && buttonFirst == HIGH){
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW); 
    digitalWrite(LED4_PIN, LOW);
    
  } // end DECODER BLOCK
  
}
