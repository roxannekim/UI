#include <AccelStepper.h>

AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper3(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

volatile byte state = LOW;

const int hallPin1 = 2;
const int hallPin2 = 3;
const int ledPin1 =  4;
const int ledPin2 =  5;
int hallState1 = LOW;
int hallState2 = LOW;
int motorSpeed = 1200;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(hallPin1, INPUT_PULLUP);
  pinMode(hallPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallPin1), blink1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hallPin2), blink2, CHANGE);
  Serial.begin(9600);

  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz
}

void loop() {
  digitalWrite(ledPin1, hallState1);
  digitalWrite(ledPin2, hallState2);

  if (hallState1 == HIGH)
  {
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorSpeed);
    stepper1.moveTo(-3000);
    stepper1.run();

    if (stepper1.distanceToGo() == 0)
      stepper1.moveTo(-stepper1.currentPosition());
    stepper1.run();
  }



  if (hallState2 == HIGH)
  {
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(-3000);
    stepper2.run();

    if (stepper2.distanceToGo() == 0)
      stepper2.moveTo(-stepper2.currentPosition());
    stepper2.run();
  }

  if (hallState1 == HIGH && hallState2 == HIGH) {
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(-3000);
    stepper3.run();

    if (stepper3.distanceToGo() == 0)
      stepper3.moveTo(-stepper3.currentPosition());
    stepper3.run();
  }

}

void blink1() {
  hallState1 = !hallState1;
}

void blink2() {
  hallState2 = !hallState2;
}
