
// ******************** LIBRAIRIES ******************
#include <arduino.h>
#include "clavier.h"



int BOUTON_QUI_EST_PRESSE;
#define val_BP1 785
#define val_BP2 600
#define val_BP3 445
#define val_BP4 300
#define val_BP5 157




bool bp(int num_bp)
{
  bool est_enfonce = false;
  int val_min, val_max;
  int val_analog = analogRead(19);

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
 return est_enfonce;
}
