  // Set the pin for the push button switch
  #define buttonPin 9
  #define ledPin 5
  #define ledPin2 13
  int n = 0;
void setup() {
  // determine status of pin as in or out
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool button = digitalRead(buttonPin); //set the button as a binary variable aka HIGH or LOW
  /** uncomment for part C&D **/
  digitalWrite(ledPin, HIGH); //pin 13 voltage on
  digitalWrite(ledPin2, LOW); //pin 10 voltage off
  /****/
  if(button==HIGH) { //if the button pin is detecting input
    /** uncomment for part A
    digitalWrite(ledPin, HIGH); //pin 13 voltage on
    delay(3000); //wait 3 secs
    **/
    /** uncomment for part B 
    int i = 0; //assign 'i' the value 0
    while (i<=9) { //while the variable i has a value less than or = 9
      digitalWrite(ledPin, HIGH); //pin 13 voltage on
      delay(250); //wait 1/4 seconds
      digitalWrite(ledPin, LOW); //set pin 13 off
      delay(250); //wait 1/4 seconds
      i++; //i goes up one but with less code
    }
    **/
    /** uncomment for part C
    digitalWrite(ledPin, LOW); //set pin 13 off
    digitalWrite(ledPin2, HIGH);//pin 10 voltage on
    delay(5000); //wait 5 seconds
    **/
    /** uncomment for part D **/
    digitalWrite(ledPin, LOW); //pin 13 voltage off
    delay(2000); //wait 2000 ms aka 2 seconds
    /****/
    /** uncomment for part E
    n++; //n goes up one
    delay(250); //wait 1/4 seconds
    if(n >= 3) { //if the value of n is greater than or equal to 3
      digitalWrite(ledPin, LOW); //set pin 13 off
      delay(250); //wait 1/4 secs
      n = 0; //reset n
    }
    **/
  }
  else {
    //digitalWrite(ledPin, HIGH); //uncomment for part E //set pin 13 on if the button isnt pushed
    digitalWrite(ledPin, LOW); //uncomment for parts A-D //set pin 13 off if the button isnt pushed
  }
}

