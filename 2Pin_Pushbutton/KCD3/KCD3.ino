int ledPin1 = 2;
int ledPin2 = 3;

int SW1 = 6;
int SW2 =7;

int SW1State;
int SW2State;


void setup() {

  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);

}

void loop() {
 SW1State = digitalRead(SW1);
 SW2State = digitalRead(SW2);
 
 if(SW1State == LOW){
   digitalWrite(ledPin1, HIGH);
 }
 else if(SW1State == HIGH){
   digitalWrite(ledPin1, LOW);
 }
if(SW2State == LOW){
   digitalWrite(ledPin2, HIGH);
 }
 else if(SW2State == HIGH){
   digitalWrite(ledPin2, LOW);
 }
  
}