#include <AccelStepper.h>

AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper3(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper4(1, 44, 46); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

volatile byte STATE = LOW;
volatile byte TRANSITION = LOW;

const int hallPin1 = 2;
const int hallPin2 = 3;
const int ledPin1 =  4;
const int ledPin2 =  5;
int hallState1 = LOW;
int hallState2 = LOW;
int motorSpeed = 1200;

bool aDown = false;
bool bDown = false;
bool cDown = false;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(hallPin1, INPUT_PULLUP);
  pinMode(hallPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallPin1), blink1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hallPin2), blink2, CHANGE);
  Serial.begin(9600);

  TWBR = ((F_CPU / 3200000l) - 16) / 2; // Change the i2c clock to 400KHz
}


void loop() {

  Serial.println(stepper1.isRunning());
  
   if (!stepper1.isRunning() || !stepper2.isRunning() || !stepper3.isRunning() ) {
      checkState();
   }

  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();
  
 //digitalWrite(ledPin1, hallState1);
 //digitalWrite(ledPin2, hallState2);

  
}

void checkState() {

if (hallState1 == HIGH && hallState2 == LOW)
  {

    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorSpeed);
    stepper1.moveTo(-300);
    //stepper1.run();
   }

if (hallState2 == HIGH && hallState1 == LOW)
  {

    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(-300);
    //stepper2.run();
  }

  if (hallState1 == HIGH && hallState2 == HIGH) {
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(-300);
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorSpeed);
    stepper4.moveTo(-300);

    //stepper3.run();
    //stepper4.run();

  }

  if (hallState1 == LOW && hallState2 == LOW) {
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorSpeed);
    stepper1.moveTo(300);
    //stepper1.run();
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(300);
    //stepper2.run();
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(300);
    //stepper3.run();
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorSpeed);
    stepper4.moveTo(300);
    //stepper4.run();

  }
  
}

void blink1() {

  hallState1 = !hallState1;

}

void blink2() {

  hallState2 = !hallState2;

}

void cup1() {

}




