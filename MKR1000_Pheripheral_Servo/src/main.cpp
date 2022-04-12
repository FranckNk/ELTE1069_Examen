/*

TITRE          : ELTE1069 Examen - Control servo moteur
AUTEUR         : Franck Nkeubou Awougang
DATE           : 12/04/2022
DESCRIPTION    : Controle d'une grue à l'aide d'un clavier matriciel sur un MKR1010 qui communique via I2C
                    à un MKR1000 et fait varier un servo moteur.
VERSION        : 0.0.1

*/



#include <Arduino.h>
#include <Wire.h>
#include <Servo.h> // pour utilisaiton du servo moteur.
#include "Timer.h"

// Declaration des classes.
Servo ServoMoteur;  // Création d'un objet de type Servo (un servo moteur).
Timer Temp;


// Déclaration des constantes.
const int PIN_SERVO_MOTEUR = 2;

char ValueGot; // Value got by I2C protocol.
unsigned short int TimeDelay    = 2000; // Wait time for serial monitor.
unsigned short int DelayAttente = 15; // Waiting time for set angle of servo.

void ReceiveEvent(int byte);

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
  Wire.begin(5);      // Démarrage du périphérique en tant que périphérique.
  Wire.onReceive(ReceiveEvent);
	// Configuration du mode des broches.
	ServoMoteur.attach(PIN_SERVO_MOTEUR);
	Temp.startTimer(2000); // Time to reset Servo.
}

void loop() {
	if (Temp.isTimerReady())
	{
		Temp.startTimer(TimeDelay);		
	}
}
void ReceiveEvent(int byte){
  	ValueGot = Wire.read();    // read one character from the I2C

		Serial.print("\nMKR1000\nLa valeur obtenue est : ");
		Serial.println(ValueGot);
}