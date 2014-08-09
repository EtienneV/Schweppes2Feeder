/*
* Fait tourner le moteur pas a pas
*
*/

#include <Stepper.h>

const int stepsPerRevolution = 48; // Nombre de pas par tour
Stepper myStepper(stepsPerRevolution, 2,3,4,5);  // Initialisation du contrôle du moteur

void setup()  {
  //Serial.begin(9600);

  pinMode(13, OUTPUT);

  myStepper.setSpeed(100);
}

void loop()
{
  digitalWrite(13, LOW);  
  myStepper.step(24); // Fait avancer d'un demi tour 
  delay(1000);

  digitalWrite(13, HIGH);  
  myStepper.step(24); // Fait avancer d'un demi tour 
  delay(1000);
}