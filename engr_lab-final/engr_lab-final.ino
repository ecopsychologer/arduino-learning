#include <Servo.h> //include the servo library
/*set the pins*/
#define buttonPin 9
#define servoPin0 10
#define servoPin1 11
#define servoPin2 12
#define servoPin3 13
#define ledPin 8
/*declare the servos*/
Servo s0;
Servo s1;
Servo s2;
Servo s3;

int counter = 0; //declare the counter variable
bool run = LOW; //declare the run variable


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); //set the button's pin as an input
  pinMode(ledPin, OUTPUT); //set the led's pin as an output
  /*attach the servos to their pins*/
  s0.attach(servoPin0); // 0/1
  s1.attach(servoPin1); // 0/2
  s2.attach(servoPin2); // 0/4
  s3.attach(servoPin3); // 0/8
}

void loop() {
  digitalWrite(ledPin, LOW); //this is for testing
  bool button = digitalRead(buttonPin);
  if ((button == HIGH) && (counter < 15)) { //if the button pin is detecting input
    run = HIGH; //set a variable run to the value high, this makes sure it is incrementing when it should be, and decrementing all other times
    digitalWrite(ledPin, HIGH); //the led stays on while the counter is incrementing or decrementing 
    Serial.println("button pressed"); //for debugging, prints this into serial every loop, while the button is pushed
    counter++; //makes sure the counter goes up
    Serial.print("counter val: "); //prints "counter val: "
    Serial.println(counter); //print the counter value, for visibility
    Serial.println(button); //prints the status of the button, 1 if pushed, 0 if not
    delay(1000); //wait a second, the whole premise of the timer
  }
  else {
    run = LOW; //start the decrementing
  }
  while (counter > 0 && run == LOW) { //this is a while loop to count down and set the servos to their binary positions
    if (counter == 0) {
      s0.write(0);
      s1.write(0);
      s2.write(0);
      s3.write(0);
    }
    else if (counter == 1) {
      s0.write(90);
      s1.write(0);
      s2.write(0);
      s3.write(0);
    }
    else if (counter == 2) {
      s0.write(0);
      servo1(HIGH);
      s2.write(0);
      s3.write(0);
    }
    else if (counter == 3) {
      s0.write(90);
      servo1(HIGH);
      servo2(LOW);
      servo3(LOW);
    }
    else if (counter == 4) {
      s0.write(0);
      servo1(LOW);
      servo2(HIGH);
      servo3(LOW);
    }
    else if (counter == 5) {
      s0.write(90);
      servo1(LOW);
      servo2(HIGH);
      servo3(LOW);
    }
    else if (counter == 6) {
      s0.write(0);
      servo1(HIGH);
      servo2(HIGH);
      servo3(LOW);
    }
    else if (counter == 7) {
      s0.write(90);
      servo1(HIGH);
      servo2(HIGH);
      servo3(LOW);
    }
    else if (counter == 8) {
      s0.write(0);
      servo1(LOW);
      servo2(LOW);
      servo3(HIGH);
    }
    else if (counter == 9) {
      s0.write(90);
      servo1(LOW);
      servo2(LOW);
      servo3(HIGH);
    }
    else if (counter == 10) {
      s0.write(0);
      servo1(HIGH);
      servo2(LOW);
      servo3(HIGH);
    }
    else if (counter == 11) {
      s0.write(90);
      servo1(HIGH);
      servo2(LOW);
      servo3(HIGH);
    }
    else if (counter == 12) {
      s0.write(0);
      servo1(HIGH);
      servo2(LOW);
      servo3(HIGH);
    }
    else if (counter == 13) {
      s0.write(90);
      servo1(LOW);
      servo2(HIGH);
      servo3(HIGH);
    }
    else if (counter == 14) {
      s0.write(0);
      servo1(HIGH);
      servo2(HIGH);
      servo3(HIGH);
    }
    else if (counter == 15) {
      s0.write(90);
      servo1(HIGH);
      servo2(HIGH);
      servo3(HIGH);
    }
    counter--;
    delay(1000);
    Serial.print("counter val: ");
    Serial.println(counter);
    Serial.println(button);
  }
}
/*************************************************************
 * these functions are a condensed way to save some time and *
 * make it visually easier to view, implemented              *
 * where convenient                                          *
 *************************************************************/
void servo0(bool val) {
  if (val == HIGH) {
    s0.write(90);
  }
  else {
    s0.write(0);
  }
}
void servo1(bool val) {
  if (val == HIGH) {
    s1.write(90);
  }
  else {
    s1.write(0);
  }
}
void servo2(bool val) {
  if (val == HIGH) {
    s2.write(90);
  }
  else {
    s2.write(0);
  }
}
void servo3(bool val) {
  if (val == HIGH) {
    s3.write(90);
  }
  else {
    s3.write(0);
  }
}
