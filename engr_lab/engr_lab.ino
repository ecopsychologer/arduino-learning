//set the pins for the leds
#define ledPin1 13
#define ledPin2 12
#define ledPin3 11
void setup() {
  //set the pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  //I forgot it auto loops
  while(1==1) {
    //all on
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
    digitalWrite(ledPin1, HIGH);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
    digitalWrite(ledPin1, HIGH);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
    digitalWrite(ledPin1, HIGH);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
    digitalWrite(ledPin1, HIGH);
    delay(250);
    digitalWrite(ledPin1, LOW);
    delay(250);
  }
}
