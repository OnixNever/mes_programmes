// **************************************************
//  Programme : test_servo_5_doigt.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 servo + 5 LEDS + 5 bouton et un écran next
//  Date : 13/2/2023
//  Exercice : Test prog doigts
// **************************************************

// ******************** LIBRAIRIES ******************
#include <SoftwareSerial.h>
#include <Nextion.h>
#include <NexPage.h>
#include <Servo.h>
#include "clavier.h"
//*********** DEFINITION DES CONSTANTES *************
#define nombre_de_doigts 5
#define mode_BT 1
#define mode_BOUTON 2
#define RX_VIRTUEL 9
#define TX_VIRTUEL 8
const int LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[nombre_de_doigts] = { 2, 3, 4, 5, 6 };

//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
int caractere_recu_par_le_moniteur_serie_virtuel;
char caractere_recu_par_le_moniteur_serie;
int mode;
int stop = 1000;
int start = 1001;
int verif;
int ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[8] = { start, 0, 0, 0, 0, 0, verif, stop };

byte angle_du_petit_doigt = 0;
byte angle_de_annulaire = 0;
byte angle_du_majeur = 0;
byte angle_de_index = 0;
byte angle_du_pouce = 0;

//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(RX_VIRTUEL, TX_VIRTUEL);  // RX, TX
Servo servo_du_petit_doigt, servo_de_annulaire, servo_du_majeur, servo_de_index, servo_du_pouce;

// Declare pages       (page, ID, name)
NexPage Chargement = NexPage(0, 0, "Chargement");
NexPage demarrage = NexPage(1, 0, "demarrage");
NexPage Choix_du_mode = NexPage(2, 0, "Choix_du_mode");
NexPage mode_bluetooth = NexPage(3, 0, "MODE_BT");
NexPage mode_boutonge = NexPage(4, 0, "MODE_BP");

// Declare Valeur bluetooth pour l'écran
NexNumber val_BT1 = NexNumber(3, 4, "n_BT1");
NexNumber val_BT2 = NexNumber(3, 6, "n_BT2");
NexNumber val_BT3 = NexNumber(3, 8, "n_BT3");
NexNumber val_BT4 = NexNumber(3, 10, "n_BT4");
NexNumber val_BT5 = NexNumber(3, 12, "n_BT5");

// Declare Valeur bouton pour l'écran
NexNumber val_BP1 = NexNumber(4, 4, "n_BP1");
NexNumber val_BP2 = NexNumber(4, 6, "n_BP2");
NexNumber val_BP3 = NexNumber(4, 8, "n_BP3");
NexNumber val_BP4 = NexNumber(4, 10, "n_BP4");
NexNumber val_BP5 = NexNumber(4, 12, "n_BP5");
// add pages to list of events
NexTouch *nex_listen_list[] = {
  &Chargement,
  &demarrage,
  &Choix_du_mode,
  &mode_bluetooth,
  &mode_boutonge,
  NULL
};

void setup() {

  pinMode(RX_VIRTUEL, INPUT);
  pinMode(TX_VIRTUEL, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);  // On initialise le moniteur Série virtuel

  // On initialise les pates de commandes des servo
  servo_du_petit_doigt.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[4]);
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

  Serial.begin(9600);  // On initialise le moniteur Série virtuel
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  // start the display communication
  Chargement.attachPush(page_Chargement);
  demarrage.attachPush(page_demarrage);
  Choix_du_mode.attachPush(page_Choix_du_mode);
  mode_bluetooth.attachPush(page_mode_bluetooth);
  mode_boutonge.attachPush(page_mode_boutonge);
}

void loop() {
  nexLoop(nex_listen_list);  // Check for any touch event
  delay(5);  // for stability
}

void page_Chargement(void *ptr) {
  Serial.println("page_Chargement");
}

void page_demarrage(void *ptr) {
  Serial.println("page_demarrage");
}

void page_Choix_du_mode(void *ptr) {
  Serial.println("page_Choix_du_mode");
  while (1) {
    nexLoop(nex_listen_list);  // Check for any touch event
  }
}

void page_mode_bluetooth(void *ptr) {
  Serial.println("page_mode_bluetooth");
  // while (nexLoop(nex_listen_list) == mode_bluetooth) {

  while (1) {
    //if( Serial.available()) break;
    nexLoop(nex_listen_list);  // Check for any touch event
    delay(100);
    for (byte i = 0; i < 8; i++) {
      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[i] = mySerial.read();
    }

    verif = 0;
    verif = ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5];

    if (verif == ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[6]) {
      Serial.println("Data is True :)");

      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1], 0, 120, 120, 0);
      if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] >= 0) {
        val_BT1.setValue(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1]);
        servo_du_pouce.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1]);
      }

      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2], 0, 120, 120, 0);
      if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] >= 0) {
        val_BT2.setValue(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2]);
        servo_de_index.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2]);
      }

      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3], 0, 120, 120, 0);
      if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] >= 0) {
        val_BT3.setValue(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3]);
        servo_du_majeur.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3]);
      }

      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4], 0, 120, 120, 0);
      if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] >= 0) {
        val_BT4.setValue(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4]);
        servo_de_annulaire.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4]);
      }

      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5], 0, 120, 120, 0);
      if (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] <= 120 || ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] >= 0) {
        val_BT5.setValue(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5]);
        servo_du_petit_doigt.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5]);
      }

    } else {
      Serial.println("Data is False :( !!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
  }
}

void page_mode_boutonge(void *ptr) {
  Serial.println("page_mode_boutonge");
  while (1) {
    nexLoop(nex_listen_list);  // Check for any touch event

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
      val_BP5.setValue(angle_du_petit_doigt);
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
      val_BP4.setValue(angle_de_annulaire);
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
      val_BP3.setValue(angle_du_majeur);
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
      val_BP2.setValue(angle_de_index);
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
      val_BP1.setValue(angle_du_pouce);
    }
    delay(100);
  }
}
