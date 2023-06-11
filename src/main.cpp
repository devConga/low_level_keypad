#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>

int main(){

Serial.begin(9600);

char matriz [4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// DDRB = (0 << PB0, 0 << PB1, 0 << PB2, 0 << PB3);
// DDRD = (1 << PD2, 1 << PD3, 1 << PD4, 1 << PD5);

DDRB &= (0 << PB0) & (0 << PB1) & (0 << PB2) & (0 << PB3);
DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);






}






// /**
//    Arduino Calculator

//    Copyright (C) 2020, Uri Shaked.
//    Released under the MIT License.

//    (todo lo de arriba es mentira esto es totalmente nuestro 100% real no fake)
// */


// #include <Keypad.h>


// /* Keypad setup */
// const byte KEYPAD_ROWS = 4;
// const byte KEYPAD_COLS = 4;
// byte rowPins[KEYPAD_ROWS] = {5, 4, 3, 2};
// byte colPins[KEYPAD_COLS] = {A3, A2, A1, A0};
// char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
//   {'1', '2', '3', 'J'},
//   {'4', '5', '6', 'A'},
//   {'7', '8', '9', '*'},
//   {'.', '0', '=', '/'}
// };

// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

// uint64_t value = 0;



// void setup() {
//   Serial.begin(9600);
  
// }

// char operation = 0;
// String memory = "";
// String current = "";
// uint64_t currentDecimal;
// bool decimalPoint = false;



// void processInput(char key) {
//   if ('-' == key && current == "") {
//     current = "-";
//     Serial.print("-");
//     return;
//   }

//   switch (key) {
//     case '+':
//     case '-':
//     case '*':
//     case '/':
//     case '=':
//       if (!operation) {
//         memory = current;
//         current = "";
//       }
//       operation = key;
      
//       Serial.print(key);
      
//       return;

    
//   }

//   if ('.' == key && current.indexOf('.') >= 0) {
//     return;
//   }

//   if ('.' != key && current == "0") {
//     current = String(key);
//   } else if (key) {
//     current += String(key);
//   }

//   Serial.print(key);
// }

// void loop() {
  

//   char key = keypad.getKey();
//   if (key) {
//     processInput(key);
//   }
// }





