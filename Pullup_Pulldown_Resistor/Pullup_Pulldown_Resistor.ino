int buttonPin1 = 5;
int buttonPin2 = 13;

int ledPin1 = 2;
int ledPin2 = 12;

int buttonState1;
int buttonState2;


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  digitalWrite(ledPin1, buttonState1);
  buttonState2 = digitalRead(buttonPin2);
  digitalWrite(ledPin2, buttonState2);
}
