// **************************************************
//  Programme : test_servo_5_doigt.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 servo + 5 LEDS + 5 bouton et un écran next
//  Date : 13/2/2023
// **************************************************

// ******************** LIBRAIRIES ******************
#include <SoftwareSerial.h>

//*********** DEFINITION DES CONSTANTES *************
#define RX_VIRTUEL 10
#define TX_VIRTUEL 11

//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(RX_VIRTUEL, TX_VIRTUEL);  // RX, TX

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  int STOP = 200;
  int START = 201;
  int VERIF = 0;
  int ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[8] = { START, 0, 0, 0, 0, 0, VERIF, STOP };

  int val_analog_du_1_doigt = analogRead(14);  // on lit la valeur de la résistance sur D1
  ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] = map(val_analog_du_1_doigt, 0, 550, 0, 120);

  int val_analog_du_2_doigt = analogRead(15);  // on lit la valeur de la résistance sur D2
  ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] = map(val_analog_du_2_doigt, 0, 550, 0, 120);

  int val_analog_du_3_doigt = analogRead(16);  // on lit la valeur de la résistance sur D3
  ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] = map(val_analog_du_3_doigt, 0, 550, 0, 120);

  int val_analog_du_4_doigt = analogRead(17);  // on lit la valeur de la résistance sur D4
  ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] = map(val_analog_du_4_doigt, 0, 550, 0, 120);

  int val_analog_du_5_doigt = analogRead(18);  // on lit la valeur de la résistance sur D5
  ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5] = map(val_analog_du_5_doigt, 0, 550, 0, 120);

  VERIF = 0;
  ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[6] = (ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[1] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[2] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[3] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[4] + ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[5]) / 10;

  Serial.print("|");
  for (byte i = 0; i < 8; i++) {
    mySerial.write(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[i]);
    Serial.print("  ");
    Serial.print(ANGLE_POUR_PILOTER_LES_SERVO_MOTEUR[i]);
    Serial.print("  ");
  }
  Serial.println("|");
}
