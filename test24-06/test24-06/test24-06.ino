#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(2, 3); // RX, TX

int laserPin = 13;

// Constante pour le seuil de la photorésistance
const int SEUIL_PHOTORESISTANCE = 90;

// Broche pour la photorésistance
const int BROCHE_PHOTORESISTANCE = A0;

// Broches pour les LED
const int BROCHE_LED_VERTE = 8;
const int BROCHE_LED_ROUGE = 9;

// Durée maximale du timer en millisecondes (30 secondes)
const unsigned long DUREE_MAX_TIMER = 30*1000; // 30 secondes

// Variables pour la photorésistance et le timer
int valeurPhotorestance;
unsigned long tempsDebut;
boolean timerActif = false;

void setup() {
  pinMode(BROCHE_PHOTORESISTANCE, INPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(BROCHE_LED_VERTE, OUTPUT);
  pinMode(BROCHE_LED_ROUGE, OUTPUT);

  digitalWrite(BROCHE_LED_VERTE, HIGH);

  bluetoothSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  valeurPhotorestance = analogRead(BROCHE_PHOTORESISTANCE);

  if (valeurPhotorestance <= SEUIL_PHOTORESISTANCE) {
    if (!timerActif) {
      tempsDebut = millis();
      timerActif = true;
    }
  } else {
    digitalWrite(BROCHE_LED_VERTE, HIGH);
    digitalWrite(BROCHE_LED_ROUGE, LOW);

    timerActif = false;
    tempsDebut = 0;
  }

  if (timerActif) {
    unsigned long tempsEcoule = millis() - tempsDebut;

    if (tempsEcoule >= DUREE_MAX_TIMER) {
      digitalWrite(BROCHE_LED_VERTE, LOW);
      digitalWrite(BROCHE_LED_ROUGE, HIGH);

      Serial.println("Il est plein");
      bluetoothSerial.println("Il est plein");

      tempsDebut = 0;
      timerActif = false;
    }
  }
  
  if (bluetoothSerial.available()) {
    String message = bluetoothSerial.readStringUntil('\n');
    if (message.equals("RESET")) {
      digitalWrite(BROCHE_LED_VERTE, HIGH);
      digitalWrite(BROCHE_LED_ROUGE, LOW);
      
      tempsDebut = 0;
      timerActif = false;
    }
  }
}
