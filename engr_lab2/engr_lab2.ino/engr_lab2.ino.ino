//set the pin for the led
#define ledPin 3
void setup() {
  //declare that the led pin is an output
  pinMode(ledPin, OUTPUT);

}

void loop() {
  //turn it on
  digitalWrite(ledPin, HIGH);
  //wait 5 seconds
  delay(5000);
  //turn it off
  digitalWrite(ledPin, LOW);
  //wait 3 seconds
  delay(3000);
  //a function to repeat 5 times, turning the led on and off 10 times, once per second
  int i = 0;
  while(i <= 9) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
    i++;
  }
}
