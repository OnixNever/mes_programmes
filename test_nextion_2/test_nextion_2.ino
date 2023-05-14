// **************************************************
//  Programme : test_servo_5_doigt.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 servo + 5 LEDS + 5 bouton et un écran next
//  Date : 13/2/2023
//  Exercice : Test prog doigts
// **************************************************

// ******************** LIBRAIRIES ******************
#include <SoftwareSerial.h>
#include "EasyNextionLibrary.h"  // Include EasyNextionLibrary
#include <Servo.h>
#include "clavier.h"

//*********** DEFINITION DES CONSTANTES *************
#define nombre_de_doigts 5
#define MODE_BT 1
#define MODE_BOUTON 2
#define RX_VIRTUEL 9
#define TX_VIRTUEL 8
#define DATA_REFRESH_RATE 100
const int LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[nombre_de_doigts] = { 2, 3, 4, 5, 6 };
//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
int Mode;
int caractere_recu_par_le_moniteur_serie_virtuel;
char caractere_recu_par_le_moniteur_serie;
int STOP = 1000;
int START = 1001;
int VERIF;
byte angle_du_petit_doigt = 0;
byte angle_de_annulaire = 0;
byte angle_du_majeur = 0;
byte angle_de_index = 0;
byte angle_du_pouce = 0;
int ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[8] = { START, 0, 0, 0, 0, 0, VERIF, STOP };
unsigned long pageRefreshTimer = millis();  // Timer for DATA_REFRESH_RATE

//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(RX_VIRTUEL, TX_VIRTUEL);  // RX, TX
Servo servo_du_petit_doigt, servo_de_annulaire, servo_du_majeur, servo_de_index, servo_du_pouce;
EasyNex myNex(Serial);

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  pinMode(RX_VIRTUEL, INPUT);
  pinMode(TX_VIRTUEL, OUTPUT);

  Serial.begin(9600);    // On initialise le moniteur Série
  mySerial.begin(9600);  // On initialise le moniteur Série virtuel
  myNex.begin(9600);     // On initialise le moniteur Série Nextion


  servo_du_petit_doigt.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[4]);  // On initialise la pate de commande à la pate du servo
  servo_de_annulaire.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[3]);
  servo_du_majeur.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[2]);
  servo_de_index.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[1]);
  servo_du_pouce.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[0]);

  int angle_glob;
  angle_glob = 0;  // Au démarrage on met tous les servo à un angle_glob de 0°
  servo_du_pouce.write(angle_glob);
  servo_de_index.write(angle_glob);
  servo_du_majeur.write(angle_glob);
  servo_de_annulaire.write(angle_glob);
  servo_du_petit_doigt.write(angle_glob);

  myNex.lastCurrentPageId = 0;
}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  myNex.NextionListen();

  refereshCurrentPage();
}



void refereshCurrentPage() {

  if ((millis() - pageRefreshTimer) > DATA_REFRESH_RATE) {


    if (myNex.currentPageId == 0) {
      refreshPage0();
    }
    pageRefreshTimer = millis();
  } else {
  }
}

void refreshPage0() {


  delay(100);
  for (byte i = 0; i < 8; i++) {
    ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[i] = mySerial.read();
  }

  VERIF = 0;
  VERIF = ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5];

  if (VERIF == ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[6]) {
    Serial.println("Data is True :)");

    ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1], 0, 120, 120, 0);
    myNex.writeNum("n_BT1.val", ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1]);

    if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] >= 0) {
      servo_du_pouce.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1]);
    }

    ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2], 0, 120, 120, 0);
    myNex.writeNum("n_BT2.val", ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2]);

    if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] >= 0) {
      servo_de_index.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2]);
    }

    ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3], 0, 120, 120, 0);
    myNex.writeNum("n_BT3.val", ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3]);

    if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] >= 0) {
      servo_du_majeur.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3]);
    }

    ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4], 0, 120, 120, 0);
    myNex.writeNum("n_BT4.val", ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4]);

    if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] >= 0) {
      servo_de_annulaire.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4]);
    }

    ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5], 0, 120, 120, 0);
    myNex.writeNum("n_BT5.val", ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5]);

    if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] >= 0) {
      servo_du_petit_doigt.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5]);
    }

  } else {
    Serial.println("Data is False :( !!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  }

  if (bp(1)) {
    switch (angle_du_petit_doigt) {
      case 0:                        // OUVRE LE DOIGT
        angle_du_petit_doigt = 120;  // On met l'angle à sa valeur max
        servo_du_petit_doigt.write(angle_du_petit_doigt);
        delay(150);
        break;

      case 120:                    // FERME LE DOIGT
        angle_du_petit_doigt = 0;  // On met l'angle à sa valeur min
        servo_du_petit_doigt.write(angle_du_petit_doigt);
        delay(150);
        break;

      default:
        break;
    }
    myNex.writeNum("n_BP5.val", angle_du_petit_doigt);
  }

  if (bp(2)) {
    switch (angle_de_annulaire) {
      case 0:                      // OUVRE LE DOIGT
        angle_de_annulaire = 120;  // On met l'angle à sa valeur max
        servo_de_annulaire.write(angle_de_annulaire);
        delay(150);
        break;

      case 120:                  // FERME LE DOIGT
        angle_de_annulaire = 0;  // On met l'angle à sa valeur min
        servo_de_annulaire.write(angle_de_annulaire);
        delay(150);
        break;

      default:
        break;
    }
    myNex.writeNum("n_BP4.val", angle_de_annulaire);
  }

  if (bp(3)) {
    switch (angle_du_majeur) {
      case 0:                   // OUVRE LE DOIGT
        angle_du_majeur = 120;  // On met l'angle à sa valeur max
        servo_du_majeur.write(angle_du_majeur);
        delay(150);
        break;

      case 120:               // FERME LE DOIGT
        angle_du_majeur = 0;  // On met l'angle à sa valeur min
        servo_du_majeur.write(angle_du_majeur);
        delay(150);
        break;

      default:
        break;
    }
    myNex.writeNum("n_BP3.val", angle_du_majeur);
  }

  if (bp(4)) {
    switch (angle_de_index) {
      case 0:                  // OUVRE LE DOIGT
        angle_de_index = 120;  // On met l'angle à sa valeur max
        servo_de_index.write(angle_de_index);
        delay(150);
        break;

      case 120:              // FERME LE DOIGT
        angle_de_index = 0;  // On met l'angle à sa valeur min
        servo_de_index.write(angle_de_index);
        delay(150);
        break;

      default:
        break;
    }
    myNex.writeNum("n_BP2.val", angle_de_index);
  }

  if (bp(5)) {
    switch (angle_du_pouce) {
      case 0:                  // OUVRE LE DOIGT
        angle_du_pouce = 120;  // On met l'angle à sa valeur max
        servo_du_pouce.write(angle_du_pouce);
        delay(150);
        break;

      case 120:              // FERME LE DOIGT
        angle_du_pouce = 0;  // On met l'angle à sa valeur min
        servo_du_pouce.write(angle_du_pouce);
        delay(150);
        break;

      default:
        break;
    }
    myNex.writeNum("n_BP1.val", angle_du_pouce);
  }
}
