#include <SoftwareSerial.h>

#include "Wire.h"
#include "LiquidCrystal_I2C.h"

SoftwareSerial bluetoothSerial(10, 11); // RX, TX

LiquidCrystal_I2C LCD(0x27,20,4); // définit le type d'écran lcd 16 x 2

void setup() {
   LCD.init(); // initialisation de l'afficheur
   LCD.backlight();
   
   LCD.setCursor(0, 0);
   LCD.print("Etat du bac :");
}

void loop() {
  if (bluetoothSerial.available()) {
    String message = bluetoothSerial.readStringUntil('\n');
    lcd.setCursor(0, 1);
    lcd.print(message);
  } else {
    LCD.setCursor(0, 1);
    LCD.print("depose possible");
  }

}
