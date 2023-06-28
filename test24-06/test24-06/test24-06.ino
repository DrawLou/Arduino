#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(2, 3); // RX, TX (broches pour la communication Bluetooth)

const int SEUIL_PHOTORESISTANCE = 300; // Seuil de valeur de la photoresistance pour détecter la luminosité
const int BROCHE_PHOTORESISTANCE = A0; // Broche analogique de la photoresistance
const int BROCHE_LED_VERTE = 8; // Broche pour la LED verte
const int BROCHE_LED_ROUGE = 9; // Broche pour la LED rouge
const unsigned long DUREE_MAX_TIMER = 10000; // Durée maximale du timer en millisecondes (10 secondes)

int laserPin = 13; // Broche pour le laser

int valeurPhotorestance;
unsigned long tempsDebut;
boolean timerActif = false; // Indicateur pour le timer actif
boolean messageEnvoye = false; // Indicateur pour le message déjà envoyé

void setup() {
  pinMode(BROCHE_PHOTORESISTANCE, INPUT); // Définit la broche de la photoresistance en entrée
  pinMode(BROCHE_LED_VERTE, OUTPUT); // Définit la broche de la LED verte en sortie
  pinMode(BROCHE_LED_ROUGE, OUTPUT); // Définit la broche de la LED rouge en sortie

  pinMode(laserPin, OUTPUT); // Définir la broche du laser en sortie

  digitalWrite(BROCHE_LED_VERTE, HIGH); // Allume la LED verte par défaut

  digitalWrite(laserPin, HIGH); // Allumer le laser

  bluetoothSerial.begin(9600); // Démarre la communication série Bluetooth à 9600 bauds
  /*Serial.begin(9600);*/ // Démarre la communication série avec l'ordinateur à 9600 bauds
}

void loop() {
  valeurPhotorestance = analogRead(BROCHE_PHOTORESISTANCE); // Lecture de la valeur de la photoresistance

  if (valeurPhotorestance <= SEUIL_PHOTORESISTANCE) { // Si la valeur est inférieure ou égale au seuil
    if (!timerActif) { // Si le timer n'est pas déjà actif
      tempsDebut = millis(); // Enregistre le temps de début du timer
      timerActif = true; // Active le timer
      messageEnvoye = false; // Réinitialise l'indicateur du message envoyé
    }
  } else {
    timerActif = false; // Désactive le timer si la valeur de la photoresistance est supérieure au seuil
  }

  if (timerActif) { // Si le timer est actif
    unsigned long tempsEcoule = millis() - tempsDebut; // Calcul du temps écoulé depuis le début du timer

    if (tempsEcoule >= DUREE_MAX_TIMER && !messageEnvoye) { // Si la durée maximale du timer est atteinte et que le message n'a pas encore été envoyé
      /*Serial.println("Il est plein");*/ // Affiche le message dans le moniteur série de l'ordinateur
      bluetoothSerial.println("Il est plein"); // Envoie le message via la communication série Bluetooth

      digitalWrite(BROCHE_LED_VERTE, LOW); // Éteint la LED verte
      digitalWrite(BROCHE_LED_ROUGE, HIGH); // Allume la LED rouge

      messageEnvoye = true; // Indique que le message a été envoyé
    }
  } else {
    digitalWrite(BROCHE_LED_VERTE, HIGH); // Allume la LED verte
    digitalWrite(BROCHE_LED_ROUGE, LOW); // Éteint la LED rouge
    messageEnvoye = false; // Réinitialise l'indicateur du message lorsqu'il n'y a pas de détection
  }
}
