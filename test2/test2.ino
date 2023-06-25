#include <SoftwareSerial.h>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

SoftwareSerial bluetoothSerial(2, 3); // RX, TX

LiquidCrystal_I2C lcd (0x27,20,4); // définit le type d'écran lcd 20 x 4

const int boutonPin = 8;
bool boutonPresse = false;

void setup() {
   lcd.init(); // initialisation de l'afficheur
   lcd.backlight();
   
   lcd.setCursor(0, 0);
   lcd.print("Etat du bac :");
   lcd.setCursor(0, 1);
   lcd.print("depose possible");
   bluetoothSerial.begin(9600);
   Serial.begin(9600);

   pinMode(boutonPin, INPUT_PULLUP); // Configure la broche du bouton en entrée avec résistance de rappel
}

void loop() {
  if (bluetoothSerial.available()) {
    String message = bluetoothSerial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Etat du bac :");
    lcd.setCursor(0, 1);
    lcd.print(message);
    Serial.println(message);
  }

  // Vérifier si le bouton a été pressé
  if (digitalRead(boutonPin) == LOW) {
    delay(50); // Délai de rebond pour éviter les faux déclenchements
    if (digitalRead(boutonPin) == LOW) {
      // Le bouton a été pressé, réinitialiser l'affichage
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Etat du bac :");
      lcd.setCursor(0, 1);
      lcd.print("depose possible");
    }
  }
}
