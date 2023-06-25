#include <SoftwareSerial.h>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

SoftwareSerial bluetoothSerial(2, 3); // RX, TX

LiquidCrystal_I2C lcd (0x27,20,4); // définit le type d'écran lcd 16 x 2

const int boutonPin = 2;
bool boutonPresse = false;

void setup() {
   lcd.init(); // initialisation de l'afficheur
   lcd.backlight();
   
   lcd.setCursor(0, 0);
   lcd.print("Etat du bac :");

   bluetoothSerial.begin(9600);
   Serial.begin(9600);
}

void loop() {
  if (bluetoothSerial.available()) {
    String message = bluetoothSerial.readStringUntil('\n');
    lcd.setCursor(0, 1);
    lcd.print(message);
    Serial.println(message);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("depose possible");
  }

  // Vérifier l'état du bouton
  if (digitalRead(boutonPin) == LOW) {
    boutonPresse = true;
  } else {
    if (boutonPresse) {
      // Envoyer un message spécial à l'émetteur pour reprendre le programme
      bluetoothSerial.println("Reprendre programme");
      boutonPresse = false;
    }
  }

}
