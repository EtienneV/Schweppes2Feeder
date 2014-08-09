/*
 * Schweppes II Feeder
 * 
 * Objectif : Permet de nourrir de façon automatisée Schweppes II
 *
 * Fonction actuelle : Fait tourner un moteur d'un demi tour
 *
 */

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{  
	stepper.setMaxSpeed(100);
	stepper.setAcceleration(300);

	stepper.moveTo(24);

	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
}

void loop()
{
    if (stepper.distanceToGo() == 0)
    {
		stepper.disableOutputs();		
		digitalWrite(13, LOW);
    }
    
    stepper.run();
}