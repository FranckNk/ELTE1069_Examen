/*

TITRE          : ELTE1069 Examen 
AUTEUR         : Franck Nkeubou Awougang
DATE           : 12/04/2022
DESCRIPTION    : Controle d'une grue à l'aide d'un clavier matriciel sur un MKR1010 qui communique via I2C
                    à un MKR1000 et fait varier un servo moteur.
VERSION        : 0.0.1

*/

#include <Arduino.h>
#include <Keypad.h>
// Configuration du clavier matriciel 4x4.

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
	{'1', '2', '3', 'A'}, 
	{'4', '5', '6', 'B'}, 
	{'7', '8', '9', 'C'}, 
	{'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  
    Serial.begin(9600);
  // put your setup code here, to run once:
 // keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}

void loop(){
    char key = keypad.getKey();

    if (key) {
        Serial.println(key);
    }
}