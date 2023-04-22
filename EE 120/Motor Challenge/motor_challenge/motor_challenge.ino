// Define necessary pins
#define MOTOR_PIN 10
#define BUTTON_PIN 13

// Keep track of fan state
bool fan_on = false;

void setup() {
  // Set pin I/O
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  // If fan is not on and button pressed, turn on fan and keep it on
  // else if fan is on and button is pressed, turn fan off and keep it off
  if (!fan_on && digitalRead(BUTTON_PIN)) {
    digitalWrite(MOTOR_PIN, HIGH);
    fan_on = true;
  }
  else if (fan_on && digitalRead(BUTTON_PIN)) {
    digitalWrite(MOTOR_PIN, LOW);
    fan_on = false;
  }
  // Add delay so button pressed registered correctly
  delay(50);
}
