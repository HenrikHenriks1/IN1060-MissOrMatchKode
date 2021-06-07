#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);        //pins til LCD
int x = 0;                                    //x er match som den tar fra Arduino1 for å avgjøre %match
void setup() {
  lcd.begin(16, 1);                           //Starter LCD
  Wire.begin(9);
  Wire.onReceive(receiveEvent);               //Gå til receiveEvent metoden
  lcd.print("Bare aa begynne :)");
}

void receiveEvent( int bytes )
{
  x = Wire.read();                            // leser en char fra l2c
}

void loop()
{ delay(500);
  if (x == 0) {                              //0 = 0% match
    delay(5000);
    lcd.clear();
    lcd.print("0% match :(");
  }

  else if (x == 1) {                         //1 = 25% match
    delay(5000);
    lcd.clear();
    lcd.print("25% Match");  
  }
  
  else if (x == 2) {                         //2 = 50% match
    delay(5000);
    lcd.clear();
    lcd.print("50% Match :)");
    
  }
  else if (x == 3) {                         //3 = 75% match
    delay(5000);
    lcd.clear();
    lcd.print("75% Match! :)");
   
  }
  else if (x == 4) {                         // 4 = 100% match
    delay(5000);
    lcd.clear();
    lcd.print("100% Match! :D");
  
  }
}
