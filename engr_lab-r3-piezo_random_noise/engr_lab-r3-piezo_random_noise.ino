#define piezoPin 3
int t = 0;
void setup() {
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  while(t==0) {
    tone(piezoPin, 2000); //play a 2000 Hz tone
    delay(1500); //wait 1.5 seconds
    t++; //invalidate the loop so we don't need to listen to the screeching buzzer
  }
  tone(piezoPin, -1); //not actually turning it off, but it is close enough
}

