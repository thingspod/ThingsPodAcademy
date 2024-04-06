//Define Arduino Pins
int buttonPin = 3;
int ledPin = 2;

void setup() {
  Serial.begin(9600);                //Initialize Serial
  pinMode(ledPin, OUTPUT);           // Initialize the LED Pin as an Output
  pinMode(buttonPin, INPUT_PULLUP);  // Initialize the Pushbutton Pin as an PULL_UP Input
}

void loop() {
  Serial.println(digitalRead(buttonPin));   // Print Sate of Pushbutton
  delay(200);                               //Delay for 200 Miliseconds
  if (digitalRead(buttonPin) == LOW)        // If pushbutton is pressing
    digitalWrite(ledPin, HIGH);             // Turn on LED
  else if (digitalRead(buttonPin) == HIGH)  //Otherwise,, Pushbutton is not pressing
    digitalWrite(ledPin, LOW);              //Turn off LED
}
