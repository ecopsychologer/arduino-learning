#include <GyverOLED.h>
#include <Wire.h>

GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
const int micPin = A0;
String lastMessage = "";

unsigned long lastUpdate = 0;
const int updateInterval = 500; // Update interval in milliseconds (half a second)
float runningAverage = 0;
const int numReadings = 10;
int readingsIndex = 0;
float readings[numReadings]; // Array to store individual sensor readings
float total = 0; // Total of the readings for averaging

void setup() {
  Serial.begin(9600);
  oled.init();
  Wire.setClock(400000L);
  oled.clear();
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  if (Serial.available() > 0) {
    lastMessage = Serial.readString();
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= updateInterval) { // Time to update the display
    lastUpdate = currentMillis;

    // Calculate the running average
    total = total - readings[readingsIndex];
    readings[readingsIndex] = convertToDecibels(analogRead(micPin));
    total = total + readings[readingsIndex];
    readingsIndex = (readingsIndex + 1) % numReadings;
    runningAverage = total / numReadings;

    // Update the display
    oled.clear();
    oled.setCursor(0, 0);
    oled.print("Avg dB: ");
    oled.print(runningAverage);
    if (lastMessage.length() > 0) {
      oled.setCursor(64, 0);
      oled.print(lastMessage);
    }
    oled.update();
  }
}

float convertToDecibels(int raw) {
  return (raw / 1023.0) * 120.0;
}
