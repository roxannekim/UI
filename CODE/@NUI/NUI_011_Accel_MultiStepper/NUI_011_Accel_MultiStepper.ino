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
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

int incomingByte = 0;

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {
  myStepper1->onestep(FORWARD, DOUBLE);
}
void backwardstep1() {
  myStepper1->onestep(BACKWARD, DOUBLE);
}
// wrappers for the second motor!
void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}


// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);


void setup()
{

  Serial.begin(9600);
  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield
  //
  //  stepper1.setMaxSpeed(200.0);
  //  stepper1.setAcceleration(200.0);
  //  stepper1.moveTo(200);
  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz

//  stepper2.setMaxSpeed(1200.0);
//  stepper2.setAcceleration(200.0);
//  stepper2.moveTo(100);

}

void loop() {

  if (Serial.available() > 0) {    // is a character available?
    incomingByte = Serial.parseInt();
    stepper2.setAcceleration(1000);
    stepper2.setMaxSpeed(incomingByte);
    //stepper2.setAcceleration(incomingByte);
    stepper2.moveTo(200);

    Serial.println(incomingByte, DEC);
  }



  if (stepper2.distanceToGo() == 0)
    stepper2.moveTo(-stepper2.currentPosition());

  stepper2.run();


}
