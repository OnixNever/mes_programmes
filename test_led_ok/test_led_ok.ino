// **************************************************
//  Programme : test_led_ok.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + LED_ROUGE
//  Date : 23/11/2022
//  Exercice : Test led
// **************************************************

// ******************** LIBRAIRIES ******************

//*********** DEFINITION DES CONSTANTES *************
#define LED 11


//******* DEFINITION DES VARIABLES GLOBALES **********
// Les variables en Minuscule

//************ DEFINITION DES OBJETS *****************

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
}
//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
}
