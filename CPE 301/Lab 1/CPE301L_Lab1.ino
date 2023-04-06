#define BUTTON_PIN 2
#define LED_PIN 4

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON_PIN) == HIGH){
        digitalWrite(LED_PIN, HIGH);
        Serial.println("BUTTON PRESSED!");
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(500);
}
