#include <Keyboard.h>
#include "Keyboard.h"

void winRun() {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(' ');
    delay(30);
    Keyboard.releaseAll();
    delay(100);
}
void setup() {
    Keyboard.begin();
    delay(2000);
    winRun();
    Keyboard.println("terminal");
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.println(""); 
    Keyboard.write(KEY_RETURN);
}

void loop() {
  // put your main code here, to run repeatedly:
  /**
   * 
   */
}
