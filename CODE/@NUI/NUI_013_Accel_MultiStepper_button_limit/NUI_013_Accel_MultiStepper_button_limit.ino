
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(300, 2);

boolean movingUp = true;
boolean zeroing = true;
boolean firstRun = true;
int sensor = LOW;
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

  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz

  AFMSbot.begin(); // Start the bottom shield
  AFMStop.begin(); // Start the top shield

  
    
}


void loop()
{
  sensor = digitalRead(6);
  
   if (firstRun == true)
   {
      Serial.print(12345);
      firstRun = false;
      
      Serial.println(sensor);
    
      //tell the motor to spin down until the limit switch is hit, then stop motorp
      stepper2.setMaxSpeed(1200);
      stepper2.setAcceleration(1200);
      stepper2.moveTo(-8000);
      stepper2.run();
   }

    stepper2.run();
   
   // set a new zero
  if (zeroing == true && sensor == HIGH) {
    zeroing = false;
    //stepper2.setMaxSpeed(1200);
    //stepper2.setAcceleration(1200);
    //stepper2.moveTo(stepper2.currentPosition());
    // delay(1000);
    Serial.print("STOP!");
    stepper2.move(0);
    //updown();

    // stepper2.run();

  } else {
    //stepper2.setMaxSpeed(1200);
    //stepper2.setAcceleration(1200);
    //stepper2.moveTo(-4000);
    //stepper2.run();
  }

}

void firstRunOld() {



}


void updown() {

  stepper2.setAcceleration(1000);
  stepper2.setMaxSpeed(1200);
  stepper2.moveTo(2000);


  if (stepper2.distanceToGo() == 0)
    stepper2.moveTo(-stepper2.currentPosition());

  stepper2.run();

}


