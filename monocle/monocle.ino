#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include <math.h>  // Include math library for trigonometric functions

// Pin configuration
#define TFT_CS  5
#define TFT_DC  4
#define TFT_RST 10

// Ring variables
#define RING_OUTER_RADIUS 120  // Outer radius of the ring
#define RING_INNER_RADIUS 110  // Inner radius of the ring
#define RING_CENTER_X 120      // X coordinate of the ring center
#define RING_CENTER_Y 120      // Y coordinate of the ring center

// Display setup
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

enum Category {
    CATEGORY1,
    CATEGORY2,
    CATEGORY3,
    CATEGORY_COUNT  // Always last
};

struct DisplayContent {
    String text;
    int textSize;
    uint16_t textColor;
};

// Array of display contents for each category
DisplayContent contents[CATEGORY_COUNT] = {
    {"Content 1", 2, GC9A01A_WHITE},
    {"Content 2", 2, GC9A01A_YELLOW},
    {"Content 3", 2, GC9A01A_RED}
};

int potPin = A0;  // Potentiometer pin
int lastCat = CATEGORY_COUNT + 1;

void setup() {
    Serial.begin(9600);
    tft.begin();
    tft.setRotation(2);  // Depending on how the display is mounted
    pinMode(potPin, INPUT);
}

void loop() {
    int potValue = analogRead(potPin);
    int category = map(potValue, 0, 1023, 0, CATEGORY_COUNT);
    category = constrain(category, 0, CATEGORY_COUNT - 1);  // Ensure category is within bounds

    if (category != lastCat) {
        updateDisplay(category);
        lastCat = category;
    }

    delay(100);
}


void updateDisplay(int category) {
    if (category >= 0 && category < CATEGORY_COUNT && category != lastCat) {
        // Clear the screen only if category changes
        tft.fillScreen(GC9A01A_BLACK);

        // Draw the ring with the current category highlighted
        drawRing(category);

        DisplayContent content = contents[category];
        
        // Set text properties
        tft.setCursor(50, 120);  // Center of the display, adjust as necessary
        tft.setTextColor(content.textColor);
        tft.setTextSize(content.textSize);

        // Display the text
        tft.println(content.text);
    }
}

void drawRing(int selectedCategory) {
    // Define the number of divisions per category for smoother arcs
    int divisionsPerCategory = 100;  // Increase this number for smoother arcs
    float angleStep = 360.0 / (CATEGORY_COUNT * divisionsPerCategory);
    uint16_t color;

    for (int i = 0; i < CATEGORY_COUNT * divisionsPerCategory; i++) {
        float angle = i * angleStep;  // Start angle of the segment
        color = (i / divisionsPerCategory == selectedCategory) ? GC9A01A_BLUE : GC9A01A_DARKGREY;

        // Calculate the start and end points for the segment
        int start_x = RING_CENTER_X + RING_INNER_RADIUS * cos(angle * DEG_TO_RAD);
        int start_y = RING_CENTER_Y + RING_INNER_RADIUS * sin(angle * DEG_TO_RAD);
        int end_x = RING_CENTER_X + RING_OUTER_RADIUS * cos(angle * DEG_TO_RAD);
        int end_y = RING_CENTER_Y + RING_OUTER_RADIUS * sin(angle * DEG_TO_RAD);

        // Draw the segment
        tft.drawLine(start_x, start_y, end_x, end_y, color);
    }
}

