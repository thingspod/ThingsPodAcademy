/*
* LED Blink Project
* Turns on an LED on for one second, then off for one second, repeatedly.
*/

//Define Variables
int ledPin = 2;

void setup() {
  // Initialize digital pin 2 as an output.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);  //Turn the LED on
  delay(1000);                 //Wait for 1000 miliseconds
  digitalWrite(ledPin, LOW);   //Turn the LED off
  delay(1000);                 //Wait for 1000 miliseconds
}
