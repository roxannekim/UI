
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(300, 2);

boolean movingUp = true;
int limitswitch = 6; // input pin of limit
int enPin = 52; // enable pin on drive
int state = 0;

void forwardstep2() {
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {
  myStepper2->onestep(BACKWARD, DOUBLE);
}

AccelStepper stepper2(forwardstep2, backwardstep2);

void setup()
{
  //  stepper.setMaxSpeed(4500);
  //  stepper.setAcceleration(400);
  //  stepper.setSpeed (800);
  pinMode(limitswitch, INPUT);   //Limit Switch

  stepper2.setCurrentPosition(0);

  stepperHome();  // stepper homing loop
  resetPos();     // set position to 0 loop
  //stepper2.stop(); // been told to call this between movements ?
  stepper2.setSpeed(0);
  delay(5000);
  // bounce();     // this wont work
}

void loop()             //main loop
{
  Serial.begin(9600);
  stepper2.moveTo(-8000);
  //stepper.setSpeed(-1500);
  stepper2.run();
}

void stepperHome()      // find home
{
  while (digitalRead(limitswitch) == LOW)
  {
    stepper2.move(100);
    stepper2.setSpeed(3500);
    stepper2.run();
  }
}

void resetPos()         //Reset position
{
  while (digitalRead(limitswitch) == HIGH)
  {
    stepper2.setCurrentPosition(0);

  }
}

//void bounce()           // bounce off or reverse of limit switch
//{
//while (state == 0)
//{
//if (stepper.currentPosition() != -4000) {
//stepper.moveTo(-4000);
//stepper.runSpeedToPosition();
//stepper.setSpeed(1500);
//stepper.run();
//}
//}
//}
