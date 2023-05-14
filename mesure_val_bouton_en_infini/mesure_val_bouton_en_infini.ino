// **************************************************
//  Programme : *.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 bouton et un écran next
//  Date : 14/05/2023
// **************************************************

//*********** DEFINITION DES CONSTANTES *************
#define INTERRUPT_PIN 19

//******* DEFINITION DES VARIABLES GLOBALES **********
int BOUTON_QUI_EST_PRESSE;

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  Serial.begin(9600);
  pinMode(19, INPUT);

}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  
    Serial.println(analogRead(19));
    delay(100);

}

