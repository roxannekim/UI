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
boolean movingUp = true;
boolean zeroing = true;
boolean firstRun = true;
int sensor = LOW;
int motorSpeed = 1200;

// wrappers for the second motor!
void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}


AccelStepper stepper2(forwardstep2, backwardstep2);


void setup()
{

  Serial.begin(9600);
  pinMode(sensor, INPUT);

  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz


}

void loop() {

  sensor = digitalRead(6);

  if (firstRun == true)
  {
   
    firstRun = false;

    Serial.println(sensor);

    //tell the motor to spin down until the limit switch is hit, then stop motorp
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(3000);
    stepper2.run();
  }

  stepper2.run();

  // set a new zero
  if (zeroing == true && sensor == HIGH) {
    zeroing = false;
   // Serial.println("STOP!");
    stepper2.move(0);
    delay(5000);
    
    incomingByte = Serial.parseInt();
    stepper2.setAcceleration(motorSpeed);
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.moveTo(-800);
  }

  if (stepper2.distanceToGo() == 0)
    stepper2.moveTo(-stepper2.currentPosition());

  stepper2.run();


}
