#include <SoftwareSerial.h>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

SoftwareSerial bluetoothSerial(2, 3); // RX, TX

LiquidCrystal_I2C lcd(0x27, 20, 4); // Définit le type d'écran lcd 16 x 2

const int boutonPin = 8;
bool boutonPresse = false;
unsigned long dernierDebounceTime = 0;
unsigned long tempsDebounce = 200;

bool affichageInitial = true;

void setup() {
  lcd.init(); // Initialisation de l'afficheur
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Etat du bac :");
  lcd.setCursor(0, 1);
  lcd.print("depose possible");

  bluetoothSerial.begin(9600);
  Serial.begin(9600);

  pinMode(boutonPin, INPUT); // Configure la broche du bouton en entrée

  digitalWrite(boutonPin, HIGH); // Active la résistance de rappel interne de l'Arduino
}

void loop() {
  // Lecture de l'état du bouton avec debouncing
  int boutonEtat = digitalRead(boutonPin);

  // Vérifier si l'état du bouton a changé
  if (boutonEtat != boutonPresse) {
    dernierDebounceTime = millis(); // Mettre à jour le dernier temps de détection de changement du bouton
  }

  // Vérifier si suffisamment de temps s'est écoulé depuis le dernier changement du bouton
  if ((millis() - dernierDebounceTime) > tempsDebounce) {
    // Mettre à jour l'état du bouton après la période de debouncing
    if (boutonEtat != boutonPresse) {
      boutonPresse = boutonEtat;

      // Vérifier si le bouton a été pressé
      if (boutonPresse == LOW) {
        // Le bouton a été pressé, réinitialiser l'affichage
        affichageInitial = true;
      }
    }
  }

  // Vérifier si un message est disponible via Bluetooth
  if (bluetoothSerial.available()) {
    String message = bluetoothSerial.readStringUntil('\n');
    if (affichageInitial) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Etat du bac :");
      affichageInitial = false;
    }
    lcd.setCursor(0, 1);
    lcd.print(message);
    Serial.println(message);
  }
}
