int buttonPin = 7;  // Arduino pin connected to button's pin
int ledPin = 2;     // Arduino pin connected to LED's pin

// variables will change:
int ledState = LOW;      // The current state of LED
int lastButtonState;     // The previous state of button
int currentButtonState;  // The current state of button

void setup() {
  Serial.begin(9600);                // Initialize serial
  pinMode(buttonPin, INPUT_PULLUP);  // Set arduino pin to input pull-up mode
  pinMode(ledPin, OUTPUT);           // Set arduino pin to output mode

  currentButtonState = digitalRead(buttonPin);
}

void loop() {
  lastButtonState = currentButtonState;         // save the last state
  currentButtonState = digitalRead(buttonPin);  // read new state

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");

    // Toggle state of LED
    ledState = !ledState;

    // Control LED arccoding to the toggled state
    digitalWrite(ledPin, ledState);
  }
}