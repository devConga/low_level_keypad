#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

int main(){

Serial.begin(115200);

char matriz [4][4]={   //La distribucion del teclado
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


// DDRB &= (0 << PB0) & (0 << PB1) & (0 << PB2) & (0 << PB3);
// DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);


// PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);



DDRB |= (1 << PB0); //PB0 en Output
DDRB &= ~(1 << PB1); //PB1 en Input


// PORTB &= ~(1 << PB1); //Sin pull-up resistor
PORTB |= (1 << PB1); //Con internal pull-up resistor

int i=1;

while(1){

  if(!(PINB & (1 << PB1))){        //Evalua si PB1 esta en LOW (0) y lo invierte con un !, asi entra al if

    Serial.print("Prendido ");
    Serial.println(i);
    i++;

  }

  
}


}

