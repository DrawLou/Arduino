#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial bluetoothSerial(2, 3); // RX, TX (broches pour la communication Bluetooth)

LiquidCrystal_I2C lcd(0x27, 20, 4); // Définit le type d'écran lcd 16 x 2

const int boutonPin = 8; // Broche du bouton
bool boutonPresse = false; // Indicateur de l'état du bouton (pressé ou non pressé)

bool affichageInitial = true; // Indicateur pour l'affichage initial

void setup() {
  lcd.init(); // Initialisation de l'afficheur LCD
  lcd.backlight();

  bluetoothSerial.begin(9600); // Démarre la communication série Bluetooth à 9600 bauds
  Serial.begin(9600); // Démarre la communication série avec l'ordinateur à 9600 bauds

  pinMode(boutonPin, INPUT); // Configure la broche du bouton en entrée sans résistance de pull-up interne

  // Affichage initial
  lcd.setCursor(0, 0);
  lcd.print("Etat du bac :");
  lcd.setCursor(0, 1);
  lcd.print("depose possible");
}

void loop() {
  // Lecture de l'état du bouton
  int boutonEtat = digitalRead(boutonPin);

  // Vérifier si le bouton a été pressé
  if (boutonEtat == LOW && !boutonPresse) {
    // Le bouton a été pressé, réinitialiser l'affichage
    Serial.println("Bouton pressé");
    affichageInitial = true;
    boutonPresse = true;
  }
  
  // Vérifier si le bouton a été relâché
  if (boutonEtat == HIGH && boutonPresse) {
    boutonPresse = false;
  }

  // Réinitialiser l'affichage si le bouton a été pressé
  if (affichageInitial) {
    lcd.setCursor(0, 1);
    lcd.print("                "); // Efface le message précédent
    lcd.setCursor(0, 1);
    lcd.print("depose possible"); // Réaffiche le message initial
    affichageInitial = false;
  }

  // Vérifier si un message est disponible via Bluetooth
  if (bluetoothSerial.available()) {
    String message = bluetoothSerial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Etat du bac :");
    lcd.setCursor(0, 1);
    lcd.print(message);
    Serial.println(message);
  }
}
