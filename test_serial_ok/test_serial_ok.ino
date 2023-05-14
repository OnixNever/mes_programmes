// **************************************************
//  Programme : test_serial_ok.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + LED_ROUGE
//  Date : 23/11/2022
//  Exercice : Test moniteur série avec led
// **************************************************

// ******************** LIBRAIRIES ******************

//*********** DEFINITION DES CONSTANTES *************
#define LED 11
//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule
int caractere_recu = 0;
//************ DEFINITION DES OBJETS *****************

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  // wait for a second
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    caractere_recu = Serial.read();

    Serial.write(caractere_recu);
    Serial.write('\n');
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    delay(100);

  }
}
