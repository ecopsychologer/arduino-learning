/* ServoTest with Arduino
   Author: Dr. JAK
   Date: 10/25/15 */
   
#include <Servo.h> // include the Servo library

Servo myservo; //create the servo object
int pos=0; //variable to store the servo position

void setup()
{
  myservo.attach(10); // attaches the servo on pin 12 to a servo object
}

void loop()
{
  for (pos=0;pos<=180;pos+=1) { // goes from 0 degrees to 180 deg in steps of 1 deg
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15 ms for the servo to reach the position
  }
  for (pos=180;pos>=0;pos-=1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15ms for the servo to reach the position
  }
  delay(10);
}
