#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3
#define baudrate 38400

String msg;

SoftwareSerial hc05(rxPin ,txPin);

/*SoftwareSerial bluetoothSerial(3, 2); // RX, TX*/

int laserPin = 13;

// Constante pour le seuil de la photorésistance
const int SEUIL_PHOTORESISTANCE = 90;

// Broche pour la photorésistance
const int BROCHE_PHOTORESISTANCE = A0;

// Broches pour les LED
const int BROCHE_LED_VERTE = 8;
const int BROCHE_LED_ROUGE = 9;

// Durée maximale du timer en millisecondes (30 secondes)
const unsigned long DUREE_MAX_TIMER = 30 * 1000;

// Variables pour la photorésistance et le timer
int valeurPhotorestance;
unsigned long tempsDebut;
boolean timerActif = false;


void setup() {
  // Configuration de la broche de la photorésistance en entrée
  pinMode(BROCHE_PHOTORESISTANCE, INPUT);

  pinMode(laserPin, OUTPUT);

  // Configuration des broches des LED en sortie
  pinMode(BROCHE_LED_VERTE, OUTPUT);
  pinMode(BROCHE_LED_ROUGE, OUTPUT);

  // Allumer la LED verte
  digitalWrite(BROCHE_LED_VERTE, HIGH);

  // Allumer le laser
  /*digitalWrite(laserPin, HIGH);*/

  // Configuration de la communication Bluetooth
  /*bluetoothSerial.begin(9600);*/

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  
  Serial.begin(38400);
  Serial.println("ENTER AT Commands:");
  hc05.begin(baudrate);

}

void loop() {
  // Lire la valeur de la photorésistance
  valeurPhotorestance = analogRead(BROCHE_PHOTORESISTANCE);

  // Vérifier si la valeur de la photorésistance est inférieure ou égale au seuil
  if (valeurPhotorestance <= SEUIL_PHOTORESISTANCE) {
    
    // La photorésistance atteint le seuil, lancer le timer si ce n'est pas déjà fait
    if (!timerActif) {
      tempsDebut = millis();
      timerActif = true;
    }
  } else {
    // La photorésistance est au-dessus du seuil, allumer la LED verte et éteindre la LED rouge
    digitalWrite(BROCHE_LED_VERTE, HIGH);
    digitalWrite(BROCHE_LED_ROUGE, LOW);
    
    // La photorésistance est au-dessus du seuil, arrêter le timer et le réinitialiser
    timerActif = false;
    tempsDebut = 0;
  }

  // Vérifier si le timer est actif
  if (timerActif) {
    // Calculer la durée écoulée en millisecondes
    unsigned long tempsEcoule = millis() - tempsDebut;

    // Vérifier si la durée maximale du timer est atteinte
    if (tempsEcoule >= DUREE_MAX_TIMER) {
       // La photorésistance atteint le seuil, allumer la LED rouge et éteindre la LED verte
      digitalWrite(BROCHE_LED_VERTE, LOW);
      digitalWrite(BROCHE_LED_ROUGE, HIGH);
      
      // Le timer est plein, afficher le message et le réinitialiser
      /*Serial.println("Il est plein");*/
      
      // Le timer est plein, envoyer le message via Bluetooth
      /*bluetoothSerial.println("Il est plein");*/
      
      tempsDebut = 0;
      // Arrêter le timer
      timerActif = false;
    }
  }

  readSerialPort();
    if(msg!="") hc05.println(msg);
    
    if (hc05.available()>0){
      Serial.write(hc05.read());
    }
}

void readSerialPort(){
  msg="";
 while (Serial.available()) {
   delay(10);  
   if (Serial.available() >0) {
     char c = Serial.read();  //gets one byte from serial buffer
     msg += c; //makes the string readString
   }
 }

}
