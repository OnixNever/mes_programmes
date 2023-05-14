// **************************************************
//  Programme : test_servo_5_doigt.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 servo + 5 LEDS + 5 bouton et un écran next
//  Date : 13/2/2023
//  Exercice : Test prog doigts
// **************************************************

// ******************** LIBRAIRIES ******************
#include <SoftwareSerial.h>

//*********** DEFINITION DES CONSTANTES *************
#define RX_VIRTUEL 9
#define TX_VIRTUEL 8

//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
int caractere_recu_par_le_moniteur_serie_virtuel;
int state = 0;
int STOP = 1000;
int START = 1001;
int VERIF;
int ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[8] = { START, 0, 0, 0, 0, 0, VERIF, STOP };


//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(RX_VIRTUEL, TX_VIRTUEL);  // RX, TX

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {  // put your setup code here, to run once
  pinMode(RX_VIRTUEL, INPUT);
  pinMode(TX_VIRTUEL, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);  // On initialise la LED de débug

  Serial.begin(9600);
  mySerial.begin(9600);

  while (!mySerial) {
    // wait for serial port to connect. Needed for native USB port only
  }
}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  if (mySerial.available()) {
    Serial.print("|");
    VERIF = 0;
    for (byte i = 0; i < 8; i++) {
      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[i] = mySerial.read();
      Serial.print("  ");
      Serial.print(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[i]);
      Serial.print("  ");
    }

    VERIF = ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5];
    if (VERIF == ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[6]) {
      Serial.print("|  ");
      Serial.println("Data is True :)");
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      Serial.print("|  ");
      Serial.println("Data is False :( !!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  delay(100);
}
