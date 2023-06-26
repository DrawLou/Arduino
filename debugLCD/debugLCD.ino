#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");

  for (byte address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println();
    }
  }
}

void loop() {}

// Arduino : 1.8.19 (Windows Store 1.8.57.0) (Windows 10), Carte : "Arduino Uno"

Le croquis utilise 3656 octets (11%) de l'espace de stockage de programmes. Le maximum est de 32256 octets.

Les variables globales utilisent 446 octets (21%) de mémoire dynamique, ce qui laisse 1602 octets pour les variables locales. Le maximum est de 2048 octets.

avrdude: ser_open(): can't open device "\\.\COM6": Acc�s refus�.




Problem uploading to board.  See https://support.arduino.cc/hc/en-us/sections/360003198300 for suggestions.



Ce rapport pourrait être plus détaillé avec
l'option "Afficher les résultats détaillés de la compilation"
activée dans Fichier -> Préférences.
