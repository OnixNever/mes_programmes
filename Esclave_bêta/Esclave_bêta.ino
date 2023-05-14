// **************************************************
//  Programme : Esclave.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 servo + 5 LEDS + 5 bouton et un écran next
//  Date : 11/3/2023
// **************************************************

// ******************** LIBRAIRIES ******************
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "fonction_mode_bluetooth.h"
#include "fonction_mode_avec_bouton.h"
#include <SoftwareSerial.h>

//*********** DEFINITION DES CONSTANTES *************
#define nombre_de_doigts 5
#define MODE_BT 1
#define MODE_AUTO 2
#define INTERRUPT_PIN 19
const int LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[nombre_de_doigts] = { 2, 3, 4, 5, 6 };

//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
int LES_MESURES_DE_TENSION_DANS_LES_SERVO_MOTEUR[nombre_de_doigts] = { 14, 15, 16, 17, 18 };
float result_calc_sur_les_mesures_des_doigts[nombre_de_doigts];
char caractere_recu_par_le_moniteur_serie_virtuel;
char caractere_recu_par_le_moniteur_serie;
byte Angle = 0;
byte Mode = 0;
byte i;

//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(9, 8);  // RX, TX virtuel
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
Servo servo_du_petit_doigt;
Servo servo_de_annulaire;
Servo servo_du_majeur;
Servo servo_de_index;
Servo servo_du_pouce;

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  Serial.begin(9600);    // On initialise le moniteur Série
  mySerial.begin(9600);  // On initialise le moniteur Série virtuel

  servo_du_petit_doigt.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[4]);
  servo_de_annulaire.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[3]);
  servo_du_majeur.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[2]);
  servo_de_index.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[1]);
  servo_du_pouce.attach(LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[0]);

  Angle = 0;  // Au démarrage on met tous les servo à un angle de 0°
  servo_du_petit_doigt.write(Angle);
  servo_de_annulaire.write(Angle);
  servo_du_majeur.write(Angle);
  servo_de_index.write(Angle);
  servo_du_pouce.write(Angle);
  
  while (!Serial) {}  // Attente de l'ouverture du moniteur série

  Serial.println(" --------------------------------------------------");
  Serial.println("|--------------------------------------------------|");
  Serial.println("|------------------ Choix du mode -----------------|");
  Serial.println("|--------- Taper 'A' pour |MODE BLUETOOTH| --------|");
  Serial.println("|---------- Taper 'C' pour |MODE BOUTON| ----------|");
  Serial.println("|--------------------------------------------------|");
  Serial.println(" --------------------------------------------------");
  Serial.println();

  while (Mode == 0)  // Permet de choisir entre le mode buetooth ou automatique
  {
    caractere_recu_par_le_moniteur_serie = Serial.read();
    switch (caractere_recu_par_le_moniteur_serie) {
      case 'A':
        Mode = MODE_BT;
        break;

      case 'C':
        Mode = MODE_AUTO;
        break;


      default:
        break;
    }
  }
  if (Mode == 1) {
    Serial.println(" --------------------------------------------------");
    Serial.println("|--------------------------------------------------|");
    Serial.println("|------- Bienvenue dans le mode |BLUETOOTH| -------|");
    Serial.println("|--------------------------------------------------|");
    Serial.println(" --------------------------------------------------");
    Serial.println();
  }

  if (Mode == 2) {
    Serial.println(" --------------------------------------------------");
    Serial.println("|--------------------------------------------------|");
    Serial.println("|-------- Bienvenue dans le mode |BOUTON| ---------|");
    Serial.println("|--------------------------------------------------|");
    Serial.println(" --------------------------------------------------");
    Serial.println();
  }
}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  if (Mode == 1) {                                                   // Mode bt
    caractere_recu_par_le_moniteur_serie_virtuel = mySerial.read();  // Lit les données du port série
    switch (caractere_recu_par_le_moniteur_serie_virtuel) {
      case 'A':  // Gestion de l'affiche et de l'actualisation
        //affiche();
        break;

      case 'Q':
        FONCTION_DU_PETIT_DOIGT_DANS_LE_MODE_BT();  // Fonction qui gère le petit doigt
        break;

      case 'S':
        FONCTION_DE_ANNULAIRE_DANS_LE_MODE_BT();  // Fonction qui gère l'annulaire
        break;

      case 'D':
        FONCTION_DU_MAJEUR_DANS_LE_MODE_BT();  // Fonction qui gère le majeur
        break;

      case 'F':
        FONCTION_DE_INDEX_DANS_LE_MODE_BT();  // Fonction qui gère l'index
        break;

      case 'G':
        FONCTION_DU_POUCE_DANS_LE_MODE_BT();  // Fonction qui gère le pouce
        break;

      default:
        break;
    }
  }

  if (Mode == 2) {

    caractere_recu_par_le_moniteur_serie = Serial.read();
    switch (caractere_recu_par_le_moniteur_serie) {
      case 'A':  // Gestion de l'affiche et de l'actualisation
        affiche();
        break;

      case 'Q':
        FONCTION_DU_PETIT_DOIGT_DANS_LE_MODE_BOUTON();  // Fonction qui gère le petit doigt
        break;

      case 'S':
        FONCTION_DE_ANNULAIRE_DANS_LE_MODE_BOUTON();  // Fonction qui gère l'annulaire
        break;

      case 'D':
        FONCTION_DU_MAJEUR_DANS_LE_MODE_BOUTON();  // Fonction qui gère le majeur
        break;

      case 'F':
        FONCTION_DE_INDEX_DANS_LE_MODE_BOUTON();  // Fonction qui gère l'index
        break;

      case 'G':
        FONCTION_DU_POUCE_DANS_LE_MODE_BOUTON();  // Fonction qui gère le pouce
        break;

      default:
        break;
    }
  }
  delay(20);


  }

  void affiche() {
    while (!Serial.available()) {}
    Serial.println(" --------------------------------------------------");
    Serial.println("|----------------------Doigts----------------------|");
    Serial.print("|---");
    for (int i = 0; i < nombre_de_doigts; i++) {

      Serial.print("-----");
      Serial.print("n°");
      Serial.print(i + 1);
    }

    Serial.println(" ------|");
    Serial.println("|--------------------------------------------------|");
    Serial.print("|----");

    for (int i = 0; i < nombre_de_doigts; i++) {
      result_calc_sur_les_mesures_des_doigts[i - 1] = analogRead(LES_MESURES_DE_TENSION_DANS_LES_SERVO_MOTEUR[i - 1]);
      result_calc_sur_les_mesures_des_doigts[i - 1] = (result_calc_sur_les_mesures_des_doigts[i - 1]) / 3.3;
      Serial.print("----");
      Serial.print(result_calc_sur_les_mesures_des_doigts[i - 1]);
    }
    Serial.println("------|");
    Serial.println("|--------------------------------------------------|");
    Serial.println(" --------------------------------------------------");
    Serial.println();
  }

  /*
  Aide Mémoire
  ============

  display.drawLine(X1,Y1,X2,Y2, SSD1306_WHITE);
  X1 et Y1 sont les coordonnées du premier point
  X2 et Y2 sont les coordonnées du deuxième pointB
  -------------------------------------------------------
  display.drawTriangle( X1,Y1,X2,Y2,X3,Y3,SSD1306_WHITE);
  -------------------------------------------------------
  display.fillCircle(X, Y, R, SSD1306_WHITE);
  X et Y sont les coordonnées du centre du cercle
  R est le rayon
  -------------------------------------------------------
  char caractere_recu_par_le_moniteur_serie;

  if (Serial.available())
  {
    caractere_recu_par_le_moniteur_serie = Serial.read();
    ...
  }
  -------------------------------------------------------
  int Valeur_num;
  float Tension;

  Valeur_num = analogRead(A3);
  Tension = Valeur_num * (3.3 / 1024.0); // Conversion en volt

  -------------------------------------------------------
  byte i,

  for(i=0; i < 5; i++){

  }
  -------------------------------------------------------
  caractere_recu_par_le_moniteur_serie;

    switch (caractere_recu_par_le_moniteur_serie) {
      case 'a':
        break;

      case 'b':
        break;

      case 'c':
        break;

      default:
        break;
    }
  ------------------------------------------------------
  while (Mode == 0)
  {

  }
  ------------------------------------------------------
  while (!Serial.available()) // Attente du choix !!!!! ATTENTION BLOQUANT !!!!! Permet dattendre la reseption d'un caractere
      {}
  ------------------------------------------------------
  while (!Serial)  // Attente de l'ouverture du moniteur série
  {}
  ------------------------------------------------------
*/
