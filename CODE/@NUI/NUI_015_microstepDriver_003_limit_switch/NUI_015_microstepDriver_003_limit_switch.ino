#include <AccelStepper.h>

// Setup Motor
const int motorSpeed = 1000;
const int zeroSpeed = 500;
const int zeroAcceleration = 800;
const int motorAcceleration = 2000;

volatile AccelStepper stepperA(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)


volatile bool aDown = false; // Stepper 1
volatile bool aMoving = false;

int zeroing = false;
volatile int aZero = false;

const int aZeroOffset = -50;
const int aBottom = -1500;

// Setup Limit Switches
const int limitPinA = 2;
volatile int limitStateA = LOW;

bool firstRun = true;


void setup()
{

  Serial.begin(9600);
  
  pinMode(limitPinA, INPUT);

  // Setup motor speed and acceleration
  stepperA.setMaxSpeed(zeroSpeed);
  stepperA.setAcceleration(zeroAcceleration);

}

void loop()
{
  // Check limit switches
  limitStateA = digitalRead(limitPinA);

 // Serial.println(limitStateA);
  
  if (firstRun == true)
  {
    Serial.println("======== First Run ========");
    zeroing = true;
    firstRun = false;
    delay(3000);// Warm up
    return;
  }
  else if ( zeroing == true ) {

    if ( limitStateA == LOW && aZero == false )
    {
      aZero = true;
      aMoving = false;
      stepperA.setCurrentPosition(0);
    }
    zeroMotors();
  }

  stepperA.run();

 }


 void zeroMotors() {


  if (limitStateA == LOW && aZero == false && aMoving == false)
      {
        Serial.println("Motor 1 Crashed");
        aZero = true;
        aMoving = false;
        stepperA.setCurrentPosition(0);
      }
      else if (aZero == false && aMoving == false) {
        Serial.println("A Moving to Zero");
        aMoving = true;
        stepperA.moveTo(10000);
      }
      else if (aZero == true && aMoving == false ) {
        Serial.println("A Moving back up");
        aMoving = true;
        stepperA.setSpeed(motorSpeed);
        stepperA.moveTo(aZeroOffset);
        stepperA.run();
        return; 
      }
      else if (aZero == true && stepperA.distanceToGo() == 0) {
        Serial.println("A New Zero");
        aMoving = false;
        stepperA.setCurrentPosition(0);
        aZero = true;
        Serial.println("Zeroing complete");
        zeroing = false;
        return;
      }

 }

