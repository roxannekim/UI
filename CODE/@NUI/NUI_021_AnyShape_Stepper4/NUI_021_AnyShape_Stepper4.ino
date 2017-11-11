#include <AccelStepper.h>
#define MODE RISING

AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper3(1, 44, 46); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper4(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

boolean movingUp = true;
boolean zeroing = true;
boolean firstRun = true;
int sensor = LOW;
int motorSpeed = 1200;

const int hallPin1 = 2;
const int hallPin2 = 3;
const int ledPin1 =  6;
const int ledPin2 =  7;
int hallState1 = 0;
int hallState2 = 0;

void setup()
{
  pinMode(ledPin1, OUTPUT);
  pinMode(hallPin1, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(hallPin2, INPUT);

  Serial.begin(9600);
  pinMode(sensor, INPUT);

  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz
}

void loop()
{
  sensor = digitalRead(13);

  if (firstRun == true)
  {

    firstRun = false;

    Serial.println(sensor);

    //tell the motor to spin down until the limit switch is hit, then stop motorp
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorSpeed);
    stepper1.moveTo(-3000);
    stepper1.run();
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(-3000);
    stepper2.run();
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(-3000);
    stepper3.run();
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorSpeed);
    stepper4.moveTo(-3000);
    stepper4.run();
  }

  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();

  // set a new zero
  if (zeroing == true && sensor == HIGH) {
    zeroing = false;
    Serial.println("STOP!");
    stepper1.move(0);
    stepper2.move(0);
    stepper3.move(0);
    stepper4.move(0);
    delay(1000);

    stepper1.setAcceleration(motorSpeed);
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.moveTo(1000);
    stepper2.setAcceleration(motorSpeed);
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.moveTo(1000);
    stepper3.setAcceleration(motorSpeed);
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.moveTo(1000);
    stepper4.setAcceleration(motorSpeed);
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.moveTo(1000);
  }

  if (stepper1.distanceToGo() == 0)
    stepper1.moveTo(-stepper1.currentPosition());
  stepper1.run();


  if (stepper2.distanceToGo() == 0)
    stepper2.moveTo(-stepper2.currentPosition());
  stepper2.run();


  if (stepper3.distanceToGo() == 0)
    stepper3.moveTo(-stepper3.currentPosition());
  stepper3.run();


  if (stepper4.distanceToGo() == 0)
    stepper4.moveTo(-stepper4.currentPosition());
  stepper4.run();

}

