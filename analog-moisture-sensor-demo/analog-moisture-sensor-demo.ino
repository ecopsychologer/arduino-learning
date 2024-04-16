#define DRY_VAL 1023 // change these on testing, 1023 is air, 60 <= water~=160 <= 280
#define WET_VAL 160

int sensor_pin = A0; 
int output_value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  output_value= analogRead(sensor_pin);
  Serial.print("Raw value : ");
  Serial.print(output_value);
  Serial.println("/1024");
  output_value = map(output_value,DRY_VAL,WET_VAL,0,100);
  Serial.print("Mositure : ");
  Serial.print(output_value);
  Serial.println("%");
  delay(1000);
}
