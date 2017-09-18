#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);

void setup() { 
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.write("Hello World!");
  lcd.setCursor(0,1);
  lcd.write("Light:");
}

void loop() {
  int sensorValue = analogRead(A0);
  lcd.setCursor(7,1);
  lcd.print(sensorValue);
  lcd.write("   ");
  delay(250);
 }