//#include <Time.h>  
//#include <Wire.h>  
//#include <DS1307RTC.h>  
#include <Stepper.h>

const int ledPin = 7;
const int interPin = 6;
const int baseDeTemps = 0;
boolean etatBaseDeTemps = 0;

boolean buffInter = 0;
boolean etatLed = 0;
boolean attente = 0;

long timerSeconde = millis();
long timerDemi = millis();

const int stepsPerRevolution = 48; 
Stepper myStepper(stepsPerRevolution, 2,3,4,5);  

void setup()  {
  //Serial.begin(9600);

  delay(2000);

  //setSyncProvider(RTC.get); 

  delay(1000);

  pinMode(ledPin, OUTPUT);
  pinMode(interPin, INPUT);

}

void loop()
{
  boolean etatInter = digitalRead(interPin);
  if(etatInter){
    buffInter = 1;

  }
  if((!etatInter) && (buffInter)){
    buffInter = 0;
    chronometre();
  }

  if(digitalRead(baseDeTemps) != etatBaseDeTemps){   
    if(digitalRead(baseDeTemps)){
      myStepper.step(1);

      digitalWrite(ledPin, HIGH); 

      timerSeconde = millis();
    }     

    etatBaseDeTemps = !etatBaseDeTemps;
    etatLed = !etatLed;
    digitalWrite(ledPin, etatLed); 
    timerDemi = millis();
  }
}

int chronometre()
{
  long debut = now();
  int continuer = 1;

  while(continuer){
    if(digitalRead(baseDeTemps) != etatBaseDeTemps){   
      if(digitalRead(baseDeTemps)){
        myStepper.step(1);

        timerSeconde = millis();
      }     

      etatBaseDeTemps = !etatBaseDeTemps;
      etatLed = !etatLed;
      digitalWrite(ledPin, etatLed); 
      timerDemi = millis();
    }

    boolean etatInter = digitalRead(interPin);
    if(etatInter){
      buffInter = 1;
    }
    if((!etatInter) && (buffInter)){

      buffInter = 0;
      attente = 1;

      while(attente){
        boolean etatInter = digitalRead(interPin);
        if(etatInter){
          buffInter = 1;

        }
        if((!etatInter) && (buffInter)){
          buffInter = 0;
          attente = 0;
          continuer = 0;
        }
        if(digitalRead(baseDeTemps) != etatBaseDeTemps){   
          if(digitalRead(baseDeTemps)){
            myStepper.step(1);
            timerSeconde = millis();
          }     

          etatBaseDeTemps = !etatBaseDeTemps;
          etatLed = !etatLed;
          digitalWrite(ledPin, etatLed); 
          timerDemi = millis();
        }
      }


    }
  }
}

