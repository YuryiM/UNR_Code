#include <LiquidCrystal.h>
#define POT 0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("FIRST NAME");
  delay(1000);
  lcd.clear();
}

void loop() {
  int data = analogRead(A0);
  int percentage = map(data, 0, 1023, 0, 100);
  delay(200);
  Serial.print("Potentiometer at ");
  Serial.print(percentage);
  Serial.print(" %\n");
  if(percentage < 33){
    lcd.print("FIRST NAME");
  }
  else if (percentage > 66){
    lcd.print("LAST NAME");
  }
  else{
    lcd.print("MIDDLE NAME");
  }
  delay(1000);
  lcd.clear();
}
