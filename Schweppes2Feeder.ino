/*
 * Schweppes II Feeder
 * 
 * Objectif : Permet de nourrir de façon automatisée Schweppes II
 *
 * Fonction actuelle : Fait tourner un moteur d'un demi tour chaque jour à une heure précise
 *
 */

#include <Time.h>
#include <TimeAlarms.h>
#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

int positionActuelle = 0;

void setup()
{
  Serial.begin(9600);
  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  // create the alarms 
  Alarm.alarmRepeat(8,29,10, MorningAlarm);  // 8:30am every day

  // Réglages vitesse et accélération du stepper
  stepper.setMaxSpeed(100);
  stepper.setAcceleration(500);

  // Initialisation de la LED
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1);

  // Si le moteur a fini sa course, on le déconnecte
  if (stepper.distanceToGo() == 0)
  {
  	if(stepper.currentPosition() == 24) // Si la cuillère est retournée
  	{
  		Alarm.delay(300); // On attend 300ms
  		stepper.moveTo(0); // Et on revient à la position de départ
  	}
  	else // Sinon, c'est qu'on doit être retourné à la position de départ
  	{
    	stepper.disableOutputs(); // On relache le moteur pour économiser de l'énergie et pour ne pas chauffer  
    	digitalWrite(13, LOW);
    }
  }
    
    stepper.run(); // Fonction gérant le stepper
}

// functions to be called when an alarm triggers:
void MorningAlarm(){
  Serial.println("Bon appétit, Schweppes II");   
  stepper.enableOutputs(); // On réactive le moteur
  stepper.moveTo(24); // On retourne la cuillère (un demi tour)
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

