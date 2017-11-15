#include <AccelStepper.h>

AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper3(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper4(1, 44, 46); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

volatile byte state = LOW;

unsigned long previousMillis1 = 0;        // will store last time LED was updated
unsigned long previousMillis2 = 0;        // will store last time LED was updated
unsigned long lastmillis = 0;

long interval = 2000;           // milliseconds of on-time

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
  attachInterrupt(digitalPinToInterrupt(hallPin1), blink1, FALLING);
  attachInterrupt(digitalPinToInterrupt(hallPin2), blink2, FALLING);
  Serial.begin(9600);

  TWBR = ((F_CPU / 400000l) - 16) / 2; // Change the i2c clock to 400KHz
}

void loop() {

  
  digitalWrite(ledPin1, hallState1);
  digitalWrite(ledPin2, hallState2);



  if ((hallState1 == HIGH) && (hallState2 == LOW)) {
    cup1();
  }

  if (hallState2 == HIGH && hallState1 == LOW)
  {
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(-300);
    stepper2.run();
  }

  if (hallState1 == HIGH && hallState2 == HIGH) {
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(-300);
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorSpeed);
    stepper4.moveTo(-300);

    stepper3.run();
    stepper4.run();

  }

  if (hallState1 == LOW && hallState2 == LOW) {
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorSpeed);
    stepper1.moveTo(300);
    stepper1.run();
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(300);
    stepper2.run();
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(300);
    stepper3.run();
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorSpeed);
    stepper4.moveTo(300);
    stepper4.run();

  }
}

void blink1() {
  unsigned long currentMillis1 = millis();

  if ((hallState1 == HIGH) && (currentMillis1 - previousMillis1 > interval))
  {
    hallState1 = !hallState1;
  } else if ((hallState1 == LOW) && (currentMillis1 - previousMillis1 > interval)) {
    hallState1 = !hallState1;

  }
  previousMillis1 = currentMillis1;
}

void blink2() {
  unsigned long currentMillis2 = millis();

  if ((hallState2 == HIGH) && (currentMillis2 - previousMillis2 > interval))
  {
    hallState2 = !hallState2;
  } else if ((hallState2 == LOW) && (currentMillis2 - previousMillis2 > interval)) {
    hallState2 = !hallState2;
  }

  previousMillis2 = currentMillis2;
}

void cup1() {
  stepper1.setMaxSpeed(motorSpeed);
  stepper1.setAcceleration(motorSpeed);
  stepper1.moveTo(-300);
  stepper1.run();
}




