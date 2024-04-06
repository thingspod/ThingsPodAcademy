#include <ezButton.h>

ezButton limitSwitch(3);  // create ezButton object that attach to pin 7;
int buzzPin = 2;

void setup() {
  Serial.begin(9600);
  limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  limitSwitch.loop(); // MUST call the loop() function first

  if(limitSwitch.isPressed()){
    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");
    digitalWrite(buzzPin, HIGH); }
  if(limitSwitch.isReleased()){
    Serial.println("The limit switch: TOUCHED -> UNTOUCHED");
    digitalWrite(buzzPin, LOW); }

  int state = limitSwitch.getState();
  if(state == HIGH){
    Serial.println("The limit switch: UNTOUCHED");
    delay(200);
  }
  else{
    Serial.println("The limit switch: TOUCHED");
    delay(200);
  }
}