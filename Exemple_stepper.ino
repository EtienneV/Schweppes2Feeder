#include <Time.h>  
#include <Wire.h>  
#include <DS1307RTC.h>  
#include <LiquidCrystal.h>
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

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup()  {
  //Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("Horloge TIPE2013");
  lcd.setCursor(0, 1);
  lcd.print("Sync RTC ...");

  delay(2000);

  setSyncProvider(RTC.get); 

  lcd.clear();
  lcd.print("Horloge TIPE2013");
  lcd.setCursor(0, 1);
  lcd.print("RTC OK !");

  delay(1000);

  pinMode(ledPin, OUTPUT);
  pinMode(interPin, INPUT);

  lcd.clear();
  lcd.print("Il est:");
  lcd.setCursor(0, 1);
  lcd.print("Date:");
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

      lcd.clear();
      lcd.print("Il est:");
      lcd.setCursor(0, 1);
      lcd.print("Date:");

      lcd.setCursor(8, 0);
      lcd.print(hour());
      lcd.print(":");
      lcd.print(minute());
      lcd.print(":");  
      lcd.print(second());
      digitalWrite(ledPin, HIGH); 

      lcd.setCursor(6, 1);
      lcd.print(day());
      lcd.print("/");
      lcd.print(month());
      lcd.print("/");  
      lcd.print(year()); 

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

        lcd.clear();
        lcd.print("Duree du TIPE :");
        lcd.setCursor(0, 1);
        lcd.print(hour(now() - debut));
        lcd.print(":");
        lcd.print(minute(now() - debut));
        lcd.print(":");  
        lcd.print(second(now() - debut));

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
      lcd.clear();
      lcd.print("Le TIPE a dure");
      lcd.setCursor(0,1);
      lcd.print(hour(now() - debut));
      lcd.print(":");
      lcd.print(minute(now() - debut));
      lcd.print(":");  
      lcd.print(second(now() - debut));

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

