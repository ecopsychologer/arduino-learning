#define piezoPin 3 //set the pin for the piezo as #3
void setup() {
  pinMode(piezoPin, OUTPUT); //declare that pin 3 is an output
}

void loop() {
  for(int i = 0; i < 4; i++) {
    tone(piezoPin, 1000); //have the piezo ring at 1000 Hz
    delay(500); //wait 0.5 seconds
    tone(piezoPin, 100); //ring at a lower, 100 Hz tone
    delay(500); //wait another half second
    //this gives us that classic beep boop of a robot
  }
  for(int n = 500; n < 4100; n++) { //make the R2D2 whistle
    if((n%5)==0){ //every 5 times
      tone(piezoPin, n); //make the tone the iteration
      delay(1); //wait a msec
    }
    delay(1); //wait another msec
  }
} 
