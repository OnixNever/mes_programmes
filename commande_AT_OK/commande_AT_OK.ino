// **************************************************
//  Programme : *.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 servo + 5 bouton et un écran next
//  Date : 14/05/2023
// **************************************************

// ******************** LIBRAIRIES ******************
#include <SoftwareSerial.h>

//************ DEFINITION DES OBJETS *****************
SoftwareSerial mySerial(10, 11);  // RX, TX

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  Serial.println("Enter AT commands:");
  mySerial.begin(38400);
}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  if (mySerial.available())
    Serial.write(mySerial.read());

  if (Serial.available())
    mySerial.write(Serial.read());
}