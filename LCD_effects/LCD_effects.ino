#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//---------------SETTINGS---------------//
#define LED_PIN 13
const unsigned short tmr1 = 500;    //Cursor flicker rate, ms
const unsigned char tmr2 = 150;     //Character output rate, ms
const unsigned char tmr3 = 200;     //LED blinking rate, ms

//---Separate elapsed time flags for cursor, text input and LED---//
unsigned long CursorPassedTime = 0;
unsigned long CharPassedTime = 0;
unsigned long LEDPassedTime = 0;

unsigned short for_i = 0;           //Variable for serial output
unsigned char CursorX, CursorY;     //Cursor coordinates

String ToWrite;                     //Queue of output

bool CursorF;                       //Flag for the cursor
bool LEDF;                          //Flag for the LED
bool FO0 = false;                   //For Once #0
bool FO1 = false;                   //For Once #1

void setup(){
  pinMode(LED_PIN, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop(){
  //---flashing the LED to demonstrate multitasking---//
  if (millis() - LEDPassedTime >= tmr3){
    if (LEDF){
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    LEDF = !LEDF;
    LEDPassedTime = millis();
  }

  //--------------------------text printing algorithm--------------------------//
  if (!FO0){CursorX = 0; CursorY = 1; FO0 = true;}     //Setting cursor for onse
  if (!FO1){                                           //Printing text fof onse
    ToWrite = """ABCDEFGHIJKLMNOPGRSTUVWXYZ              it works!!!"""; 
    FO1 = true;
  }

  //----------Printing the text----------//
  if (ToWrite != ""){
    if (millis() - CharPassedTime >= tmr2){
      if (for_i < ToWrite.length()){
        lcd.setCursor(CursorX, CursorY);
        CharPassedTime = millis();
        CursorX++;
        lcd.print(ToWrite[for_i]);
        for_i++;
      } else {
        ToWrite = "";
        for_i = 0;
      }
    }
  }

  //---------blinking the cursor---------//
  if (millis() - CursorPassedTime >= tmr1){
    lcd.setCursor(CursorX, CursorY);
    CursorPassedTime = millis();
    if(CursorF){
      lcd.write(255);
    } else {
      lcd.print(" ");
    }
    CursorF = !CursorF;
  }

  //---moving to the next line---//
  if (CursorX>19){
    CursorX = 0;
    CursorY++;
  }
}