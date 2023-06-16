#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

int evaluarFila();
int evaluarColumna();

void columnasInput();
void columnasOutput();
void iniciarTimer0();
// void setup();
// void loop();

volatile bool teclaFlag = false;
bool cambio = false; 

int columna = -1, fila = -1;

char ultEstado = 'Z';

  char matriz [4][4]={   //La distribucion del teclado
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

void setup(){
    Serial.begin(115200);
    columnasInput();      //Inicializa los estados de los pines de filas y columnas
    sei();
}

void loop(){
    if((PINB & 0b00001111) != 15){
        iniciarTimer0();
        if(teclaFlag){
            columna=evaluarColumna();
            _delay_ms(10);
            columnasOutput();
            _delay_ms(10);
            fila=evaluarFila();
            _delay_ms(10);
            columnasInput();
            if((ultEstado != matriz[fila][columna]) || cambio){      
              if((fila>=0) && (columna>=0)){
                Serial.println(matriz[fila][columna]);
                ultEstado = matriz[fila][columna];
                }
                teclaFlag = false;
                cambio = false;
            }
        }
    }
    else if((PINB & 0b00001111) == 15){        //No hay ninguna tecla presionada por cierto tiempo
        iniciarTimer0();
        if(!teclaFlag){
            cambio = true;      //Se puede volver a ingresar la misma tecla
        }
    }
}

void iniciarTimer0(){
  TCCR0A |= (1 << WGM01);         //Timer0 en modo CTC
  TCCR0B |= (1 << CS01)  ;        //Prescaler en /8 
  OCR0A = 249;
  TIMSK0 |= (1 << OCIE0A);        //Interrupt en Compare Match A
}

ISR(TIMER0_COMPA_vect){
    //Serial.println(TCNT0);
  if((PINB & 0b00001111) != 15){
    teclaFlag = true;
  }
  else teclaFlag = false;
}

void columnasInput(){

  DDRB &= ~(1 << PB0) & ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3) & ~(1 << PB4) & ~(1 << PB5);      
  // PB0, PB1, PB2 y PB3 (Columnas) seteados a INPUT 
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
  
  return -1;
}

int evaluarFila(){

  if(!(PIND & (1 << PD2))){                       // Evalua si se presiona algun boton de la 1ra fila
    return 0;
  }

  if(!(PIND & (1 << PD3))){                       // Evalua si se presiona algun boton de la 2da fila
    return 1;
  }

  if(!(PIND & (1 << PD4))){                       // Evalua si se presiona algun boton de la 3ra fila
    return 2;
  }

  if(!(PIND & (1 << PD5))){                       // Evalua si se presiona algun boton de la 4ta fila
    return 3;
  }

  return -1;
}
