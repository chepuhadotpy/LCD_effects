#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const unsigned short tmr1 = 500;    //Cursor flicker rate, ms
const unsigned short tmr2 = 200;    //Character output rate, ms
unsigned long PassedTime = 0;

String ToWrite;                     //Queue of output
unsigned char CursorX, CursorY;
bool CursorF;
unsigned short for_i = 0;           //Variable for serial output

bool FO0 = false;                   //For Once #0
bool FO1 = false;                   //For Once #1

void setup(){
  lcd.init();
  lcd.backlight();
}

void loop(){
  /*###some code################
  ############################*/
  if (!FO0){CursorX = 1; CursorY = 1; FO0 = true;}
  if (!FO1){ToWrite = "Hi!"; FO1 = true;}
  /*###some code################
  ############################*/
  
  //-------мигание курсором----------//
  if (millis() - PassedTime >= tmr1){
    lcd.setCursor(CursorX, CursorY);
    PassedTime = millis();
    if(CursorF){
      lcd.write(255);
    } else {
      lcd.print(" ");
    }
    CursorF = !CursorF;
  }

  if (ToWrite != ""){
    if (millis() - PassedTime >= tmr2){
      if (for_i < ToWrite.length()){
        lcd.setCursor(CursorX, CursorY);
        PassedTime = millis();
        CursorX++;
        lcd.print(ToWrite[for_i]);
        for_i++;
      } else {
        ToWrite = "";
        for_i = 0;
      }
    }
  }
}