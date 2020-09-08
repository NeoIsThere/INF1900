#define F_CPU 8000000
#include <util/delay.h> //correct car avr-gcc connaît ces répertoires
#include <avr/io.h> 

int main()
{
  float freq = (float)1000/(float)60; //60Hz

  DDRA = 0xff; // toutes les broches du PORT A sont en mode sortie (0b11111111) car fournissent du courant
  DDRD = 0x00; // toutes les broches du PORT D sont en mode entrée car l'alimentation électrique y est connecté
  int ajout =1;

  PORTA =0; // prendra les valeurs xxxxxx01, xxxxxx10, xxxxxx00 en boucle      

  for(;;)  // boucle sans fin
  {
    //01: couleur verte
    PORTA +=1;

    //10: couleur rouge
    _delay_ms (3000);
    PORTA +=1;
    _delay_ms (3000);

    //alternance 10 / 01: couleur ambrée
    bool negatif = 1; 
    for(int i=0; i<180; i++ ){ //3000ms
      ajout = negatif ? -1:1;
      PORTA += ajout;
      negatif = !negatif; //l'ajout alterne entre -1, +1 pour passer de 01 à 10 (vert à rouge) en boucle
      _delay_ms (freq); //60Hz
    }
    //le compteur arrive dans la boucle du dessus a 10 et ressort à 10 donc +2 pour le rammener à 0 (on veut pas passer par 11)
    PORTA +=2;
  
  }
  return 0; 
}
