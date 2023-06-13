#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

int evaluarFila();

void columnasInput();
void columnasOutput();

int main(){

Serial.begin(115200);

char matriz [4][4]={   //La distribucion del teclado
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};


  columnasInput();

  int fila=-1, columna=-1;

  while(1){

    
    if(!(PINB & (1 << PB0))){                        // Evalua si se presiona algun boton de la 1ra columna
      // Serial.println("1C");
      columna=0;
      fila=evaluarFila();
    }

    if(!(PINB & (1 << PB1))){                       // Evalua si se presiona algun boton de la 2da columna
      // Serial.println("2C");
      columna=1;
      fila=evaluarFila();
    }

    if(!(PINB & (1 << PB2))){                       // Evalua si se presiona algun boton de la 3ra columna
      // Serial.println("3C");
      columna=2;
      fila=evaluarFila();
    }

    if(!(PINB & (1 << PB3))){                       // Evalua si se presiona algun boton de la 4ta columna
      // Serial.println("4C");
      columna=3;
      fila=evaluarFila();
    }


    if(columna>=0 && fila>=0){
      Serial.println(matriz[fila][columna]);
      
    }


    columna=-1;
    fila=-1;

    
  }

}

  


void columnasInput(){

  DDRB &= ~(1 << PB0) & ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3);        // PB0, PB1, PB2 y PB3 seteados a INPUT 
  DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);            // PD2, PD3, PD4 y PD5 seteados a OUTPUT


  PORTD &= ~(1 << PD2) & ~(1 << PD3) & ~(1 << PD4) & ~(1 << PD5);
  PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);           // Se habilitan los pull-up resistors de todos los INPUT

}

void columnasOutput(){

  DDRD &= ~(1 << PD2) & ~(1 << PD3) & ~(1 << PD4) & ~(1 << PD5);        
  DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);      


  PORTB &= ~(1 << PB0) & ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3);
  PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);      

}

int evaluarFila(){

  columnasOutput();
  
  while(1){

    if(!(PIND & (1 << PD2))){                        // Evalua si se presiona algun boton de la 1ra columna
      columnasInput();
      return 0;
    }

    if(!(PIND & (1 << PD3))){                       // Evalua si se presiona algun boton de la 2da columna
      columnasInput();
      return 1;
    }

    if(!(PIND & (1 << PD4))){                       // Evalua si se presiona algun boton de la 3ra columna
      columnasInput();
      return 2;
    }

    if(!(PIND & (1 << PD5))){                       // Evalua si se presiona algun boton de la 4ta columna
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




