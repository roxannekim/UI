#include <AccelStepper.h>
#define MODE RISING

AccelStepper stepperA(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepperB(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)


int incomingByte = 0;
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
  //  stepperA.setAcceleration(1500); // acceleration in steps per second
  //  stepperA.setMaxSpeed(1100);    // maximum speed

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
    stepperA.setMaxSpeed(motorSpeed);
    stepperA.setAcceleration(motorSpeed);
    stepperA.moveTo(-3000);
    stepperA.run();
    stepperB.setMaxSpeed(motorSpeed);
    stepperB.setAcceleration(motorSpeed);
    stepperB.moveTo(-3000);
    stepperB.run();
  }

  stepperA.run();
  stepperB.run();

  hallState1 = digitalRead(hallPin1);
  hallState2 = digitalRead(hallPin2);

  if (hallState1 == HIGH && hallState2 == LOW) {
    attachInterrupt(0, CUP1, MODE);
    attachInterrupt(1, CUP1, MODE);

  }
  if (hallState1 == LOW && hallState2 == HIGH) {
    stepperA.setAcceleration(motorSpeed);
    stepperA.setMaxSpeed(motorSpeed);
    stepperA.moveTo(1000);
    stepperB.setAcceleration(motorSpeed);
    stepperB.setMaxSpeed(motorSpeed);
    stepperB.moveTo(1000);

    attachInterrupt(0, CUP2, MODE);
    attachInterrupt(1, CUP2, MODE);
  }

  if (hallState1 == HIGH && hallState2 == HIGH) {
    stepperA.setAcceleration(motorSpeed);
    stepperA.setMaxSpeed(motorSpeed);
    stepperA.moveTo(1000);
    stepperB.setAcceleration(motorSpeed);
    stepperB.setMaxSpeed(motorSpeed);
    stepperB.moveTo(1000);
    attachInterrupt(0, PHONE, MODE);
    attachInterrupt(1, PHONE, MODE);
  }
  if (hallState1 == LOW && hallState2 == LOW) {
    stepperA.setAcceleration(motorSpeed);
    stepperA.setMaxSpeed(motorSpeed);
    stepperA.moveTo(1000);
    stepperB.setAcceleration(motorSpeed);
    stepperB.setMaxSpeed(motorSpeed);
    stepperB.moveTo(1000);
    attachInterrupt(0, N, MODE);
    attachInterrupt(1, N, MODE);
  }
  // set a new zero
  if (zeroing == true && sensor == HIGH) {
    zeroing = false;
    Serial.println("STOP!");
    stepperA.move(0);
    stepperB.move(0);
    delay(1000);


  }
}


void CUP1() {
  Serial.println("CUP1");
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);

  stepperA.setAcceleration(motorSpeed);
  stepperA.setMaxSpeed(motorSpeed);
  stepperA.moveTo(1000);
  stepperB.setAcceleration(motorSpeed);
  stepperB.setMaxSpeed(motorSpeed);
  stepperB.moveTo(1000);


  if (stepperA.distanceToGo() == 0)
    stepperA.moveTo(-3000);
  stepperA.run();


  if (stepperB.distanceToGo() == 0)
    stepperB.moveTo(3000);
  stepperB.run();
}

void CUP2() {
  Serial.println("CUP2");
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);

  if (stepperA.distanceToGo() == 0)
    stepperA.moveTo(-3000);
  stepperA.run();

  if (stepperB.distanceToGo() == 0)
    stepperB.moveTo(3000);
  stepperB.run();
}

void PHONE() {
  Serial.println("PHONE");
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);

  if (stepperA.distanceToGo() == 0)
    stepperA.moveTo(-stepperA.currentPosition());
  stepperA.run();

  if (stepperB.distanceToGo() == 0)
    stepperB.moveTo(-stepperB.currentPosition());
  stepperB.run();

}

void N() {
  Serial.println("N");
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  if (stepperA.distanceToGo() == 0)
    stepperA.moveTo(0);
  stepperA.run();

  if (stepperB.distanceToGo() == 0)
    stepperB.moveTo(0);
  stepperB.run();
}

void NONE() {
  Serial.println("NONE");
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  if (stepperA.distanceToGo() == 0)
    stepperA.moveTo(0);
  stepperA.run();

  if (stepperB.distanceToGo() == 0)
    stepperB.moveTo(0);
  stepperB.run();

}


