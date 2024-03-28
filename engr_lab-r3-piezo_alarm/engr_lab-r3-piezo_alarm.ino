#define piezoPin 3 //set the pin for the piezo as #3
void setup() {
  pinMode(piezoPin, OUTPUT); //declare that pin 3 is an output
}

void loop() {
  for(int i = 0; i < 4; i++) { //in order to have optimal annoyance, we replicated the 
    //*BEEP* *BEEP* *BEEP* (rest) tone from digital alarm clocks
    tone(piezoPin, 3000); //set the piezo to operate at 3000 Hz
    delay(100); //wait 0.1 seconds
    tone(piezoPin, -1); //turn that annoyance off
    delay(100); //for only one tenth of a second
  } //it runs 3 times, then
  delay(750); //it waits 3/4 of a second
}
