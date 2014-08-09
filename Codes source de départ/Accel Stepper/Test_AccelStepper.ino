// Random.pde
// -*- mode: C++ -*-
//
// Make a single stepper perform random changes in speed, position and acceleration
//
// Copyright (C) 2009 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

void setup()
{  
	stepper.setMaxSpeed(100);
	stepper.setAcceleration(10);

	stepper.moveTo(24);
}

void loop()
{
    if (stepper.distanceToGo() == 0)
    {
		stepper.disableOutputs();		
    }
    
    stepper.run();
}
