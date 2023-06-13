#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

int evaluarFila();
int evaluarColumna();

void columnasInput();
void columnasOutput();
void iniciarTimer0();

bool teclaPress();

volatile bool teclaFlag = false; 


int main(){


  Serial.begin(9600);

  char matriz [4][4]={   //La distribucion del teclado
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };


  columnasInput();      //Inicializa los estados de los pines de filas y columnas

  int fila=-1, columna=-1;
  iniciarTimer0();

  while(1){

    if(teclaFlag){
      fila=evaluarFila();
      columna=evaluarColumna();

      if(columna>=0 && fila>=0){
        Serial.println(matriz[fila][columna]);
      }

      columna=-1;
      fila=-1;
    }
  }
}

void iniciarTimer0(){
  TCCR0A |= (1 << WGM01);         //Timer0 en modo CTC, el interrupt sucede a los 32ms aprox
  TCCR0B |= (1 << CS02);
  OCR0A = 0b01111100;
  TIMSK0 |= (1 << OCIE0A);
}

bool teclaPress(){
  int fila=evaluarFila();
  int columna=evaluarColumna();

  if(columna>=0 && fila>=0){
        return true;
      }
  return false;
}

ISR(TIMER0_COMPA_vect){
 /* if(teclaPress()){
    teclaFlag = true;
  }
  else teclaFlag = false;*/
}

void columnasInput(){

  DDRB &= ~(1 << PB0) & ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3);        // PB0, PB1, PB2 y PB3 (Columnas) seteados a INPUT 
  DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);            // PD2, PD3, PD4 y PD5 (Filas) seteados a OUTPUT


  PORTD &= ~(1 << PD2) & ~(1 << PD3) & ~(1 << PD4) & ~(1 << PD5);
  PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);           // Se habilitan los pull-up resistors de las columnas 

}

void columnasOutput(){

  DDRD &= ~(1 << PD2) & ~(1 << PD3) & ~(1 << PD4) & ~(1 << PD5);        // PD2, PD3, PD4 y PD5 (Filas) seteados a INPUT
  DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);            // PB0, PB1, PB2 y PB3 (Columnas) seteados a OUTPUT


  PORTB &= ~(1 << PB0) & ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3);
  PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);           // Se habilitan los pull-up resistors de las filas

}

int evaluarColumna(){

  while(1){
    if(!(PINB & (1 << PB0))){                       // Evalua si se presiona algun boton de la 1ra columna
      return 0;
    }

    if(!(PINB & (1 << PB1))){                       // Evalua si se presiona algun boton de la 2da columna
      return 1;
    }

    if(!(PINB & (1 << PB2))){                       // Evalua si se presiona algun boton de la 3ra columna
      return 2;
    }

    if(!(PINB & (1 << PB3))){                       // Evalua si se presiona algun boton de la 4ta columna
      return 3;
    }
  }
}

int evaluarFila(){

  columnasOutput();                                 // Invierte los estados de filas y columnas
  
  while(1){

    if(!(PIND & (1 << PD2))){                       // Evalua si se presiona algun boton de la 1ra fila
      columnasInput();                              // Devuelve filas y columnas al estado original
      return 0;
    }

    if(!(PIND & (1 << PD3))){                       // Evalua si se presiona algun boton de la 2da fila
      columnasInput();
      return 1;
    }

    if(!(PIND & (1 << PD4))){                       // Evalua si se presiona algun boton de la 3ra fila
      columnasInput();
      return 2;
    }

    if(!(PIND & (1 << PD5))){                       // Evalua si se presiona algun boton de la 4ta fila
      columnasInput();
      return 3;
    }

  }

 


}






//--------------------------------------------------------------Esta es la prueba del boton------------------------------------------------------------------

// DDRB |= (1 << PB0); //PB0 en Output
// DDRB &= ~(1 << PB1); //PB1 en Input


// // PORTB &= ~(1 << PB1); //Sin pull-up resistor
// PORTB |= (1 << PB1); //Con internal pull-up resistor

// int i=1;

// while(1){

//   if(!(PINB & (1 << PB1))){        //Evalua si PB1 esta en LOW (0) y lo invierte con un !, asi entra al if

//     Serial.print("Prendido ");
//     Serial.println(i);
//     i++;

//   }

  
// }




