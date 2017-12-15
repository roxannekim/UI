
#include <AccelStepper.h>

AccelStepper stepperA(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)


int incomingByte = 0;
boolean movingUp = true;
boolean zeroing = true;
boolean firstRun = true;
int sensor = LOW;
int motorSpeed = 1200;

void setup()
{

  Serial.begin(9600);
  pinMode(sensor, INPUT);
//  stepperA.setAcceleration(1500); // acceleration in steps per second
//  stepperA.setMaxSpeed(1100);    // maximum speed

  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz
}

void loop()
{
  sensor = digitalRead(6);

  if (firstRun == true)
  {

    firstRun = false;

    Serial.println(sensor);

    //tell the motor to spin down until the limit switch is hit, then stop motorp
    stepperA.setMaxSpeed(motorSpeed);
    stepperA.setAcceleration(motorSpeed);
    stepperA.moveTo(-3000);
    stepperA.run();
  }

  stepperA.run();

  // set a new zero
  if (zeroing == true && sensor == HIGH) {
    zeroing = false;
    // Serial.println("STOP!");
    stepperA.move(0);
    delay(5000);

    incomingByte = Serial.parseInt();
    stepperA.setAcceleration(motorSpeed);
    stepperA.setMaxSpeed(motorSpeed);
    stepperA.moveTo(1000);
  }

  if (stepperA.distanceToGo() == 0)
    stepperA.moveTo(-stepperA.currentPosition());

  stepperA.run();


  //  stepperA.runToNewPosition(10000);
  //  stepperA.run();
  //  delay(2000);
  //
  //  stepperA.runToNewPosition(-10000);
  //  stepperA.run();
  //  delay(2000);
}
