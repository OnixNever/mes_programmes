// **************************************************
//  Programme : test_servo_5_doigt.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 servo + 5 LEDS + 5 bouton et un écran next
//  Date : 13/2/2023
//  Exercice : Test prog doigts
// **************************************************

// ******************** LIBRAIRIES ******************
#include <SoftwareSerial.h>
#include <Servo.h>

//*********** DEFINITION DES CONSTANTES *************
#define nombre_de_doigts 5
#define RX_VIRTUEL 9
#define TX_VIRTUEL 8
#define RX_VIRTUEL 9
#define TX_VIRTUEL 8
const int LES_PATES_DE_COMMANDE_DANS_LES_SERVO_MOTEUR[nombre_de_doigts] = { 2, 3, 4, 5, 6 };

//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
int caractere_recu_par_le_moniteur_serie_virtuel;
int state = 0;
int STOP = 1001;
int START = 1000;
int VERIF = 0;
int ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[8] = { START, 0, 0, 0, 0, 0, VERIF, STOP };


//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(RX_VIRTUEL, TX_VIRTUEL);  // RX, TX
Servo servo_du_petit_doigt, servo_de_annulaire, servo_du_majeur, servo_de_index, servo_du_pouce;

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {                   // put your setup code here, to run once
  pinMode(LED_BUILTIN, OUTPUT);  // On initialise la LED de débug
  pinMode(RX_VIRTUEL, INPUT);
  pinMode(TX_VIRTUEL, OUTPUT);
  Serial.begin(9600);    // On initialise le moniteur Série
  mySerial.begin(9600);  // On initialise le moniteur Série virtuel

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
      delay(100);
    }

    VERIF = ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5];


    if (VERIF == ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[6]) {
      Serial.print("|  ");
      Serial.println("Data is True :)");
      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1], 0, 120, 120, 0);
      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2], 0, 120, 120, 0);
      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3], 0, 120, 120, 0);
      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4], 0, 120, 120, 0);
      ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] = map(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5], 0, 120, 120, 0);

      servo_du_pouce.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1]);
      servo_de_index.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2]);
      servo_du_majeur.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3]);
      servo_de_annulaire.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4]);
      servo_du_petit_doigt.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5]);

    } else {
      Serial.print("|  ");
      Serial.println("Data is False :( !!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }
  }
}
