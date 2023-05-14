// **************************************************
//  Programme : *.ino
//  Auteur : Dahnine Daoud 6ème Electronique INRACI
//  Hardware : Arduino nano + 5 bouton
//  Date : 14/05/2023
// **************************************************

//****************************************************
//*************** INITIALISATION *********************
//****************************************************
void setup() {
  Serial.begin(9600);  
}

//****************************************************
//*************** BOUCLE INFINIE *********************
//****************************************************
void loop() {
  int val_analog_du_1_doigt = analogRead(14);
  val_analog_du_1_doigt = map(val_analog_du_1_doigt, 0, 500, 0, 120);  // map (valeur, limite_basse_source, limite_haute_source, limite_basse_destination, limite_haute_destination)
  int val_analog_du_2_doigt = analogRead(15);
  val_analog_du_2_doigt = map(val_analog_du_2_doigt, 0, 500, 0, 120);
  int val_analog_du_3_doigt = analogRead(16);
  val_analog_du_3_doigt = map(val_analog_du_3_doigt, 0, 500, 0, 120);
  int val_analog_du_4_doigt = analogRead(17);
  val_analog_du_4_doigt = map(val_analog_du_4_doigt, 0, 500, 0, 120);
  int val_analog_du_5_doigt = analogRead(18);
  val_analog_du_5_doigt = map(val_analog_du_5_doigt, 0, 500, 0, 120);

  Serial.print("valeur doigt n°1 = ");
  Serial.println(val_analog_du_1_doigt);
  Serial.print("valeur doigt n°1 = ");
  Serial.print("valeur doigt n°2 = ");
  Serial.println(val_analog_du_2_doigt);
  Serial.print("valeur doigt n°3 = ");
  Serial.println(val_analog_du_3_doigt);
  Serial.print("valeur doigt n°4 = ");
  Serial.println(val_analog_du_4_doigt);
  Serial.print("valeur doigt n°5 = ");
  Serial.println(val_analog_du_5_doigt);
  delay(100);
}
