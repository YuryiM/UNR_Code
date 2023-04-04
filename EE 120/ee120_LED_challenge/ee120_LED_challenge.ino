// Define LED Pins
#define RED_PIN 8
#define GREEN_PIN 9
#define BLUE_PIN 10

// Define Button Pin
#define BUTTON_PIN 11

// Define Global LED State Variables
int currentState = 0;
int oldState = 0;

void setup() {
  // Set button to input
  pinMode(BUTTON_PIN, INPUT);

  // Set LEDs to output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Set LED default state to OFF
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

void loop() {
  // Read state of the button (invert state)
  int buttonState = !digitalRead(BUTTON_PIN);

  // If button on
  if(buttonState){
    // Verify button being pressed, wait 25ms
    delay(25);
    // Read button state again
    buttonState = !digitalRead(BUTTON_PIN);
    // Once button released, update LED color
    if(!buttonState){ currentState = oldState + 1; }
  }
  // 75ms delay
  else{ delay(75); }

  // Switch statement to update LEDs
  switch(currentState){
    case 1:
      // White
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, HIGH);
      oldState = currentState;
      break;
    case 2:
      // Red
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, LOW);
      oldState = currentState;
      break;
    case 3:
      // Yellow
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, LOW);
      oldState = currentState;
      break;
    case 4:
      // Purple
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, HIGH);
      oldState = currentState;
      break;
    case 5:
      // Green
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, LOW);
      oldState = currentState;
      break;
    case 6:
      // Cyan
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(BLUE_PIN, HIGH);
      oldState = currentState;
      break;
    case 7:
      // Blue
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
      digitalWrite(BLUE_PIN, HIGH);
      oldState = currentState;
      break;
    default:
      // All LEDs OFF
      digitalWrite(RED_PIN,LOW);
      digitalWrite(GREEN_PIN,LOW);
      digitalWrite(BLUE_PIN,LOW);
      oldState = 0;
      break;
  }
}
