// **************************************************
//  Programme : Master.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 module "ZD10-100"
//  Date : 11/3/2023
// **************************************************

// ******************** LIBRAIRIES ******************
#include <SoftwareSerial.h>
//*********** DEFINITION DES CONSTANTES *************
#define RX_VIRTUEL 10
#define TX_VIRTUEL 11
//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
char caractere_recu_par_le_moniteur_serie_virtuel;
char caractere_recu_par_le_moniteur_serie;

//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(RX_VIRTUEL, TX_VIRTUEL);  // RX, TX

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  Serial.begin(9600);  // On initialise le moniteur Série
  mySerial.begin(9600);  // On initialise le moniteur Série virtuel
  delay(100);
}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  caractere_recu_par_le_moniteur_serie = Serial.read();  // Reads the data from the serial port
  switch (caractere_recu_par_le_moniteur_serie) {
    case 'A':  // Gestion de l'affiche et de l'actualisation
      mySerial.write('A');
      Serial.println("on envoie 0");
      break;

    case 'Q':
      mySerial.write('Q');
      Serial.println("on envoie 1");
      break;

    case 'S':
      mySerial.write('S');
      Serial.println("on envoie 2");
      break;

      case 'D':
      mySerial.write('D');
      Serial.println("on envoie 2");
      break;

      case 'F':
      mySerial.write('F');
      Serial.println("on envoie 2");
      break;
      
      case 'G':
      mySerial.write('G');
      Serial.println("on envoie 2");
      break;

    default:
      break;
  }
}
