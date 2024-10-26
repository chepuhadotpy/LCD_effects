#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


void setup(){
  lcd.init();
  lcd.backlight();
  coolWrite("abcdefg");
}

void loop(){

}


void coolWrite(String str){
  String printedStr;
  for (int c = 0; c < str.length(); c++){
    printedStr += str[c];
    lcd.print(printedStr);
    lcd.write(255);
    delay(300);
    if (c != str.length()-1){
      lcd.clear();
    }
  }
}