#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(2, 3); // RX, TX

const int SEUIL_PHOTORESISTANCE = 300;
const int BROCHE_PHOTORESISTANCE = A0;
const int BROCHE_LED_VERTE = 8;
const int BROCHE_LED_ROUGE = 9;
const unsigned long DUREE_MAX_TIMER = 20000; // 20 secondes

int valeurPhotorestance;
unsigned long tempsDebut;
boolean timerActif = false;
boolean messageEnvoye = false;

void setup() {
  pinMode(BROCHE_PHOTORESISTANCE, INPUT);
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
      messageEnvoye = false;
    }
  } else {
    timerActif = false;
  }

  if (timerActif) {
    unsigned long tempsEcoule = millis() - tempsDebut;

    if (tempsEcoule >= DUREE_MAX_TIMER && !messageEnvoye) {
      Serial.println("Il est plein");
      bluetoothSerial.println("Il est plein");

      digitalWrite(BROCHE_LED_VERTE, LOW);
      digitalWrite(BROCHE_LED_ROUGE, HIGH);

      messageEnvoye = true;
    }
  } else {
    digitalWrite(BROCHE_LED_VERTE, HIGH);
    digitalWrite(BROCHE_LED_ROUGE, LOW);
    messageEnvoye = false; // Réinitialiser la variable lorsqu'il n'y a pas de détection
  }
}
