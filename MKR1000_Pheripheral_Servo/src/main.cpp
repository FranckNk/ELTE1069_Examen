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
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"
#include <Servo.h> // pour utilisaiton du servo moteur.
#include "Timer.h"

// Declaration des classes.
Servo ServoMoteur;  // Création d'un objet de type Servo (un servo moteur).
Timer Temp;
Timer TempSend;


// Déclaration des constantes.
const int PIN_SERVO_MOTEUR = 2;
const int LED_PIN = 4;

bool LedState = false;
bool Blink = false;
bool SendData = false;
char ValueGot; // Value got by I2C protocol.
unsigned short int TimeDelay    = 500; // Wait time for blink LED.
unsigned short int DelayAttente = 15; // Waiting time for set angle of servo.
unsigned short int AngleServo = 0; // Valeur par défaut de l'angle du servo moteur.

void ReceiveEvent(int byte);

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	
	wifiConnect();                  //Branchement au réseau WIFI
	MQTTConnect();                  //Branchement au broker MQTT

	Wire.begin(5);      // Démarrage du périphérique en tant que périphérique.
	Wire.onReceive(ReceiveEvent);

	// Configuration du mode des broches.
	ServoMoteur.attach(PIN_SERVO_MOTEUR);
	ServoMoteur.write(AngleServo);              // Reset la valeur de l'angle du servo.

	Temp.startTimer(2000); // Time to reset Servo.
}

void loop() {
	// Modification de l'angle du servo moteur.
	ServoMoteur.write(AngleServo);     
	// Vérification de l'état de blink.
	if (AngleServo <= 0){
		Blink = false;
		digitalWrite(LED_PIN, LedState);   
	}
	else {
		Blink = true;
	}
	if (Temp.isTimerReady() && Blink)
	{         
		digitalWrite(LED_PIN, LedState);   
		LedState = !LedState;
		Temp.startTimer(TimeDelay);		
	}
	if (SendData)
	{
		appendPayload("ValeurAngleServo", AngleServo);
		sendPayload();
		SendData = false;
	}
	

}
void ReceiveEvent(int byte){
	ValueGot = Wire.read();    // read one character from the I2C

	Serial.print("\nMKR1000\nLa valeur obtenue est : ");
	Serial.println(ValueGot);
	Serial.print("AngleServo : ");
	Serial.println(AngleServo);
	SendData = true;
	switch (ValueGot)
	{
	case 'A':
		AngleServo = 180;
		break;
	case 'B':
			if (AngleServo >= 180)
				AngleServo = 180;
			else
				AngleServo = AngleServo + 1;
		break;
	case 'C':
		if (AngleServo <= 0)
				AngleServo = 0;
			else
				AngleServo = AngleServo - 1;
		break;
	case 'D':
		AngleServo = 0;
		LedState = false;
		break;
	
	default:
		break;
	}
}