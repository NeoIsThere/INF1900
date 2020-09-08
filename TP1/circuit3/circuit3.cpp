#define F_CPU 8000000
#include <util/delay.h> //correct car avr-gcc connaît ces répertoires
#include <avr/io.h> 

bool isButtonPushed(){
  if(PIND & 0x04){
    _delay_ms(10);
    if(PIND & 0x04)
        return true;
  }
  return false;
 }

int main()
{

  DDRA = 0xff; // toutes les broches du PORT A sont en mode sortie (0b11111111) car fournissent du courant
  DDRD = 0x00; // toutes les broches du PORT D sont en mode entrée car l'alimentation électrique y est connecté
                 
  for(;;)  // boucle sans fin
  {
    if(isButtonPushed())
      PORTA =1;
    else
      PORTA =0;
  } 
}
