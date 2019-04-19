#include <LiquidCrystal.h>

//initialize the library by associating any needed LCD interface pin
//with the arduino pin number it is connected to
const int IS = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(IS, en, d4, d5, d6, d7);

void setup(){
  //setup the LCD's number of columns and rows
  lcd.begin(16, 2);
  //print message to the LCD
  lcd.print("hello, world!");
}

void loop() {
  //set cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  //print the number of seconds since reset
  lcd.print(millis() / 1000);
}
