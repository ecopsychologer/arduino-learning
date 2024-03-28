/* VideoGameSound with Arduino
   Author: Dr. JAK
   Date: 10/25/15 */
   
int pin=3; //declare the pin to be number 3

void setup() {
  pinMode(pin,OUTPUT); //set said pin as the output
  Serial.begin(9600); //open the serial monitor @ 9600 baud
}

void loop() {
  for(int duration=15; duration>=1; duration=duration-1) { //declare the duration to be 15
    //continue until duration < 1
    //and subtract one from the duration each time the loop completes
    for(int freq=1700;freq<=2300;freq=freq+20){ //similar deal, but with frequency, and incrementing up 20, from 1700 => 2300
      tone(pin,freq,duration); //set the tone of pin 3 to be the variable 'freq' and to last for the duration 'duration'
      Serial.print(freq); //print the frequency to serial
      Serial.print(" "); //print a space
      Serial.println(duration); //print the duration
    }
  }
}

