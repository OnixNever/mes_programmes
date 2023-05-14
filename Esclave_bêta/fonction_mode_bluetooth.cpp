
// ******************** LIBRAIRIES ******************
#include <arduino.h>
#include <Servo.h>
#include "fonction_mode_bluetooth.h"

//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
extern byte Angle;
extern Servo servo_du_petit_doigt;
extern Servo servo_de_annulaire;
extern Servo servo_du_majeur;
extern Servo servo_de_index;
extern Servo servo_du_pouce;

void FONCTION_DU_PETIT_DOIGT_DANS_LE_MODE_BT() {
  Serial.println("Le petit doigt doit bouger");
  switch (Angle) {
    case 0:         // OUVRE LE DOIGT
      Angle = 120;  // On met l'angle à sa valeur max
      servo_du_petit_doigt.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    case 120:     // FERME LE DOIGT
      Angle = 0;  // On met l'angle à sa valeur min
      servo_du_petit_doigt.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    default:
      break;
  }
}

void FONCTION_DE_ANNULAIRE_DANS_LE_MODE_BT() {
  Serial.println("L'annulaire doit bouger");
  switch (Angle) {
    case 0:         // OUVRE LE DOIGT
      Angle = 120;  // On met l'angle à sa valeur max
      servo_de_annulaire.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    case 120:     // FERME LE DOIGT
      Angle = 0;  // On met l'angle à sa valeur min
      servo_de_annulaire.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    default:
      break;
  }
}

void FONCTION_DU_MAJEUR_DANS_LE_MODE_BT() {
  Serial.println("Le majeur doit bouger");
  switch (Angle) {
    case 0:         // OUVRE LE DOIGT
      Angle = 120;  // On met l'angle à sa valeur max
      servo_du_majeur.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    case 120:     // FERME LE DOIGT
      Angle = 0;  // On met l'angle à sa valeur min
      servo_du_majeur.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    default:
      break;
  }
}
void FONCTION_DE_INDEX_DANS_LE_MODE_BT() {
  Serial.println("L'index doit bouger");
  switch (Angle) {
    case 0:         // OUVRE LE DOIGT
      Angle = 120;  // On met l'angle à sa valeur max
      servo_de_index.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    case 120:     // FERME LE DOIGT
      Angle = 0;  // On met l'angle à sa valeur min
      servo_de_index.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    default:
      break;
  }
}

void FONCTION_DU_POUCE_DANS_LE_MODE_BT() {
  Serial.println("Le pouce doit bouger");
  switch (Angle) {
    case 0:         // OUVRE LE DOIGT
      Angle = 125;  // On met l'angle à sa valeur max
      servo_du_pouce.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    case 125:     // FERME LE DOIGT
      Angle = 0;  // On met l'angle à sa valeur min
      servo_du_pouce.write(Angle);
      Serial.print("Angle=");
      Serial.println(Angle);
      break;

    default:
      break;
  }      
}
