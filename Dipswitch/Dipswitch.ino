int dipPin1 = 7;
int dipPin2 = 6;
int dipPin3 = 5;
int dipPin4 = 4;

int ledPin1 = 11;
int ledPin2 = 10;
int ledPin3 = 9;
int ledPin4 = 8;

int dipState1;
int dipState2;
int dipState3;
int dipState4;

void setup() {

pinMode(ledPin1,OUTPUT);
pinMode(ledPin2,OUTPUT);
pinMode(ledPin3,OUTPUT);
pinMode(ledPin4,OUTPUT);

pinMode(dipPin1, INPUT_PULLUP);
pinMode(dipPin2, INPUT_PULLUP);
pinMode(dipPin3, INPUT_PULLUP);
pinMode(dipPin4, INPUT_PULLUP);


}

void loop() {
dipState1 = digitalRead(dipPin1);
digitalWrite(ledPin1, dipState1);
dipState2 = digitalRead(dipPin2);
digitalWrite(ledPin2, dipState2);
dipState3 = digitalRead(dipPin3);
digitalWrite(ledPin3, dipState3);
dipState4 = digitalRead(dipPin4);
digitalWrite(ledPin4, dipState4);


}
