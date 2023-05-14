
// ******************** LIBRAIRIES ******************
#include <arduino.h>
#include "clavier.h"

//*********** DEFINITION DES CONSTANTES *************

#define val_BP1 785
#define val_BP2 600
#define val_BP3 445
#define val_BP4 300
#define val_BP5 157

//******* DEFINITION DES VARIABLES GLOBALES **********
int BOUTON_QUI_EST_PRESSE;

bool bp(int num_bp) {

  bool est_enfonce = false;  // Variable qui stocker l'état du bouton poussoir
  int val_min, val_max;      // Variables pour stocker les valeurs minimale et maximale des boutons

  // En fonction du numéro de bouton poussoir, on initialise les valeurs minet max 
  switch (num_bp) {
    case 1:
      val_min = val_BP1 - 10;
      val_max = val_BP1 + 10;
      break;
    case 2:
      val_min = val_BP2 - 10;
      val_max = val_BP2 + 10;
      break;
    case 3:
      val_min = val_BP3 - 10;
      val_max = val_BP3 + 10;
      break;
    case 4:
      val_min = val_BP4 - 10;
      val_max = val_BP4 + 10;
      break;
    case 5:
      val_min = val_BP5 - 10;
      val_max = val_BP5 + 10;
      break;
  }

  est_enfonce = (val_analog < val_max) && (val_analog > val_min);

  return est_enfonce;  // On retourne l'état du bouton poussoir
}