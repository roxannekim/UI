// Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(300, 2);


// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
//void forwardstep1() {  
//  myStepper1->onestep(FORWARD, SINGLE);
//}
//void backwardstep1() {  
//  myStepper1->onestep(BACKWARD, SINGLE);
//}
// wrappers for the second motor!
void forwardstep2() {  
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, DOUBLE);
}

boolean movingUp = true;

AccelStepper stepper2(forwardstep2, backwardstep2);


void setup()
{  
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
     
  stepper2.setMaxSpeed(600.0);
  stepper2.setAcceleration(200.0);
  stepper2.moveTo(-4000);
}

void loop()
{
    // Change direction at the limits
//    if (stepper1.distanceToGo() == 0)
//	stepper1.moveTo(-stepper1.currentPosition());

    if (stepper2.distanceToGo() == 0) {
      if (movingUp){
  	    stepper2.moveTo(0);
        movingUp = false;
      } else {
        stepper2.moveTo(-4000);
        movingUp = true;
      }
    }

//    stepper1.run();
    stepper2.run();

}

