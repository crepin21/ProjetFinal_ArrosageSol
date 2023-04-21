#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos                  = 0;    // variable to store the servo position
bool posi                = 0;   
const int greenLedPin    = 2; // Pin de la LED verte
const int redLedPin      = 3; // Pin de la LED rouge
const int yellowLedPin   = 4; // Pin de la LED jaune

bool ConditionSyst    = 0; 
bool EtatPinVert      = 0;

// Durée minimale entre deux arrosages  (en secondes)
int SecDuration  = 60;

//Nombre d'activation de la valve
  int Activation = 0;

// Dernier temps d'arrosage
unsigned long LastWaterTime = 0;

/*
  # the sensor value description
  # 0  ~300     dry soil
  # 300~700     humid soil
  # 700~950     in water
*/

void setup(){

  Serial.begin(9600);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  pinMode(greenLedPin, OUTPUT); // Configuration de la LED verte en sortie
  pinMode(redLedPin, OUTPUT); // Configuration de la LED rouge en sortie

  // Initialisation de la dernière minute d'arrosage
  LastWaterTime = millis();


}

void loop(){

int sensorValue = analogRead(A0); // Lecture de la valeur du capteur d'humidité

  Serial.print("Moisture Sensor Value:");
  Serial.println(sensorValue);

  // Vérification si le sol a besoin d'être arrosé (En verifiant l'humidite et le dernier temps d'arrosage)
  if (sensorValue < 300 && (millis() - LastWaterTime) >= (SecDuration * 1000)) //Retirer le delai pour montrer le pb
  {
    if(posi == 1)
    {
      for (pos = 0; pos <= 180; pos += 1) 
      { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
      }
      posi = 0; 
    }
    digitalWrite(greenLedPin, HIGH); // Allumage de la LED verte
    EtatPinVert = 0; 
    digitalWrite(redLedPin, LOW); // Extinction de la LED rouge
    // Enregistrement de l'heure d'arrosage
    LastWaterTime = millis();
  } 
  else 
  {
    if(posi == 0)
    {
      for (pos = 180; pos >= 0; pos -= 1) 
      { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
      }
      digitalWrite(greenLedPin, LOW); // Extinction de la LED verte 
      EtatPinVert = 1;
      digitalWrite(redLedPin, HIGH); // Allumage de la LED rouge
      posi = 1;
    }
  }
    delay(100);

}