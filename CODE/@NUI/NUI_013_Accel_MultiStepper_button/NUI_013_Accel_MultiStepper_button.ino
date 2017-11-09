
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(300, 2);

boolean movingUp = true;
int sensor = 0;
int location = 0;

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
  pinMode(13, OUTPUT);

  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz

  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  // stepper2.setMaxSpeed(600.0);
  //stepper2.setAcceleration(200.0);
  stepper2.moveTo(4000);
}

void loop()
{

  sensor = analogRead(A0);
  Serial.println(sensor);

  if (stepper2.distanceToGo() == 0) {

    if (sensor == 1023) {
      stepper2.setSpeed(0);

      //      stepper2.moveTo(0);
      //      movingUp = false;

    } else {
      stepper2.setSpeed(600);
      stepper2.moveTo(600);
      movingUp = true;


    }
  }
  stepper2.run();
}

