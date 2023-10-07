//Define Variables
int ledPin1 = 3;
int ledPin2 = 5;

int brightness1 = 0;    // How Bright the LED1 is
int brightness2 = 255;  // How Bright the LED2 is

int fadeAmount = 5;  // how many points to fade the LED by

void setup() {
  pinMode(ledPin1, OUTPUT);  // Declare PWM Pin3(LED1) to Be an Output
  pinMode(ledPin2, OUTPUT);  // Declare PWM Pin5(LED2) to Be an Output
}

void loop() {
  analogWrite(ledPin1, brightness1);  // Set the Brightness of Pin 3

  // change the brightness for next time through the loop:
  brightness1 = brightness1 + fadeAmount;
  // reverse the direction of the fading at the ends of the fade:
  if (brightness1 <= 0 || brightness1 >= 255) {
    fadeAmount = -fadeAmount;
  }

  analogWrite(ledPin2, brightness2);  // Set the Brightness of Pin 5

  // change the brightness for next time through the loop:
  brightness2 = brightness2 - fadeAmount;
  // reverse the direction of the fading at the ends of the fade:
  if (brightness2 <= 0 || brightness2 >= 255) {
    fadeAmount = +fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}