#include <GyverOLED.h>

GyverOLED<SSD1306_128x64> oled;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  oled.init();
  oled.clear();
  oled.update();
}

void loop() {
  // put your main code here, to run repeatedly:


  // --------------------------
  // Controls
  //oled.setContrast(10);   // between 0..255
  //oled.setPower(true);    // true/false
  //oled.flipH(true);       // true/false - horizontal flip
  //oled.flipV(true);       // true/false - vertical flip
  //oled.isEnd();           // возвращает true, если дисплей "кончился" - при побуквенном выводе
  //oled.setScale(3);
  //oled.invertText(true);    // invert text color!
  //oled.autoPrintln(true);   // auto new line as needed, very handy
  //oled.print(F("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam"));
  //oled.dot(0, 0);     // dot at x,y
  //oled.line(5, 5, 10, 10);        // line from x0,y0 to x1,y1
  //oled.setScale(2);
  //oled.fastLineH(0, 5, 10);       // горизонтальная линия (y, x1, x2)
  //oled.fastLineV(0, 5, 10);       // аналогично верт. линия (x, y1, y2)
  //oled.rect(20, 20, 30, 25);      // rectangle (x0,y0,x1,y1)
  //oled.rect(5, 35, 35, 60, OLED_STROKE);      // прямоугольник (x0,y0,x1,y1)
  // options:
  // OLED_CLEAR - очистить
  // OLED_FILL - залить
  // OLED_STROKE - нарисовать рамку
  //oled.roundRect(50, 5, 80, 25, OLED_STROKE);  // аналогично скруглённый прямоугольник
  //oled.circle(60, 45, 15, OLED_STROKE);        // окружность с центром в (x,y, с радиусом)
  //oled.circle(60, 45, 5, OLED_FILL);           // четвёртый аргумент: параметр фигуры
}
