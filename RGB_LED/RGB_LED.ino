//Define Arduino Pins
int redPin = 13;
int greenPin = 12;
int bluePin = 11;

void setup() {
  //Configure Arduino Pins to the Output Mode
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  //Control LED to Emit this Color (Red: 0, Green: 201, Blue: 204)
  analogWrite(redPin, 0);
  analogWrite(greenPin, 201);
  analogWrite(bluePin, 204);
  delay(1000);

  //Control LED to Emit this Color (Red: 210, Green: 15, Blue: 187)
  analogWrite(redPin, 210);
  analogWrite(greenPin, 15);
  analogWrite(bluePin, 187);
  delay(1000);

  //Control LED to Emit this Color (Red: 50, Green: 50, Blue: 50)
  analogWrite(redPin, 50);
  analogWrite(greenPin, 50);
  analogWrite(bluePin, 50);
  delay(1000);
}
