 
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
  Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day 
  Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

 
  Alarm.timerRepeat(5, Repeats);            // timer for every 15 seconds    
  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 

  stepper.setMaxSpeed(100);
  stepper.setAcceleration(500);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1); // wait one second between clock display

  if (stepper.distanceToGo() == 0)
    {
    stepper.disableOutputs();   
    digitalWrite(13, LOW);
    }
    
    stepper.run();
}

// functions to be called when an alarm triggers:
void MorningAlarm(){
  Serial.println("Alarm: - turn lights off");    
}

void EveningAlarm(){
  Serial.println("Alarm: - turn lights on");           
}

void WeeklyAlarm(){
  Serial.println("Alarm: - its Monday Morning");      
}

void ExplicitAlarm(){
  Serial.println("Alarm: - this triggers only at the given date and time");       
}

void Repeats(){
  Serial.println("15 second timer"); 
  stepper.enableOutputs();
  positionActuelle = (positionActuelle + 24)%48;
  stepper.moveTo(positionActuelle);        
}

void OnceOnly(){
  Serial.println("This timer only triggers once");  
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

