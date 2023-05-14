
// **************************************************
//  Programme : *.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 bouton
//  Date : 14/05/2023
// **************************************************

//*********** DEFINITION DES CONSTANTES *************
#define val_BP1 785
#define val_BP2 600
#define val_BP3 445
#define val_BP4 300
#define val_BP5 157

//******* DEFINITION DES VARIABLES GLOBALES **********
int BOUTON_QUI_EST_PRESSE;
byte petit_doigt = "";
byte annulaire = "";
byte majeur = "";
byte index = "";
byte pouce = "";

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

  if (bp(1))
    Serial.println("bp1");
  if (bp(2))
    Serial.println("bp2");
  if (bp(3))
    Serial.println("bp3");
  if (bp(4))
    Serial.println("bp4");
  if (bp(5))
    Serial.println("bp5");

  delay(500);
}

bool bp(int num) {
  bool est_enfonce = false;
  int val_analog = analogRead(19);

  switch (num) {

    case 1:
      est_enfonce = (val_analog < (val_BP1 + 10)) && (val_analog > (val_BP1 - 10));
      break;

    case 2:
      est_enfonce = (val_analog < (val_BP2 + 10)) && (val_analog > (val_BP2 - 10));
      break;

    case 3:
      est_enfonce = (val_analog < (val_BP3 + 10)) && (val_analog > (val_BP3 - 10));
      break;

    case 4:
      est_enfonce = (val_analog < (val_BP4 + 10)) && (val_analog > (val_BP4 - 10));
      break;

    case 5:
      est_enfonce = (val_analog < (val_BP5 + 10)) && (val_analog > (val_BP5 - 10));
      break;
  }
  return est_enfonce;
}