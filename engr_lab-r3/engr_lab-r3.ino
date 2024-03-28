#define piezoPin 3
void setup() {
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  int t = random(0, 2000);
  int n = random(0, 1023);
  analogWrite(piezoPin, n);
  delay(t);
}
