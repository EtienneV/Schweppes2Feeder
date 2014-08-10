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
  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day

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
    stepper.disableOutputs();   
    digitalWrite(13, LOW);
  }
    
    stepper.run(); // Fonction gérant le stepper
}

// functions to be called when an alarm triggers:
void MorningAlarm(){
  Serial.println("Alarm: - turn lights off");   
  stepper.enableOutputs();
  positionActuelle = (positionActuelle + 24)%48;
  stepper.moveTo(positionActuelle);         
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

