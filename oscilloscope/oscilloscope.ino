void setup() {
  Serial.begin(115200); //initialize serial in
  //Serial.begin(38400);
}

void loop() {
  int signal = analogRead(A0); //read the signal coming in
  //signal = signal/10; //reduce the signal size to eliminate noise
  //delay(1); //to slow the signal
  Serial.println(signal, 3); //print the signal with 4 sig figs
}
