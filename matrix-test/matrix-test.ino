#include <GyverMAX7219.h>

// Define the number of matrices horizontally (W) and vertically (H) and the CS pin.
// Since you're using a custom CLK pin, we have to define DATA and CLK as well.
MAX7219<1, 1, 10, 16, 15> mtrx; // 1x1 matrix, CS pin is 10, DATA pin is 16 (MOSI), CLK pin is 15

void setup() {
  mtrx.begin();  // Initialize the matrix
  mtrx.setBright(0);  // Set initial brightness to minimum

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  // Read potentiometers
  int potX = analogRead(A1);  // Read potentiometer on A1
  int potY = analogRead(A2);  // Read potentiometer on A2
  int potBrightness = analogRead(A3);  // Read potentiometer on A3 for brightness

  // Map the potentiometer value to matrix size (0-7 for an 8x8 matrix)
  int x = map(potX, 0, 1023, -1, 8);
  int y = map(potY, 0, 1023, -1, 8);

  // Map the third potentiometer for brightness (-1 is off, 15 is max)
  int brightness = map(potBrightness, 0, 1023, 0, 15);

  mtrx.clear(); // Clear the matrix
  mtrx.setBright(brightness);  // Set the brightness
  
  // Turn on LEDs based on potentiometer values
  for (int i = 0; i <= x; i++) {
    for (int j = 0; j <= y; j++) {
      mtrx.dot(i, j, true); // Turn on the dot at (i, j)
    }
  }
  mtrx.update();  // Update the display with the changes
  delay(100);  // Small delay to make changes noticeable
}
