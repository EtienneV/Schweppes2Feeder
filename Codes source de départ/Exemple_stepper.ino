/*
* Fait tourner le moteur pas a pas
*
*/

#include <Stepper.h>

const int stepsPerRevolution = 48; // Nombre de pas par tour
Stepper myStepper(stepsPerRevolution, 2,3,4,5);  // Initialisation du contrôle du moteur

void setup()  {
  //Serial.begin(9600);
}

void loop()
{
  myStepper.step(1); // Fait avancer d'un pas   

  delay(500); // On attend une demi seconde
}