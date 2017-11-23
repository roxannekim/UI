#include <AccelStepper.h>

AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper3(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper4(1, 44, 46); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

volatile byte STATE = LOW;
volatile byte TRANSITION = LOW;

#define switchPin1 49
#define switchPin2 51
#define switchPin3 53
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

const int hallPin1 = 2;
const int hallPin2 = 3;
int hallState1 = LOW;
int hallState2 = LOW;
int motorSpeed = 2000;

int checkTime = 0;
int currentTime = 0;

bool aDown = false;
bool bDown = false;
bool cDown = false;

void setup() {
  pinMode (switchPin1, INPUT);
  pinMode (switchPin2, INPUT);
  pinMode (switchPin3, INPUT);

  pinMode(hallPin1, INPUT_PULLUP);
  pinMode(hallPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallPin1), blink1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hallPin2), blink2, CHANGE);
  Serial.begin(9600);

  TWBR = ((F_CPU / 3200000l) - 16) / 2; // Change the i2c clock to 400KHz
}


void loop() {

  buttonState1 = digitalRead(switchPin1);
  buttonState2 = digitalRead(switchPin2);
  buttonState3 = digitalRead(switchPin3);
  Serial.print(buttonState1);
  Serial.print("  /  ");
  Serial.print(buttonState2);
  Serial.print("  /  ");
  Serial.println(buttonState3);

  currentTime = millis();

  if (!stepper1.isRunning() && !stepper2.isRunning() && !stepper3.isRunning() && !stepper4.isRunning() && currentTime - checkTime > 250 ) {
    //Serial.println("No motors running");
    //checkState();
    runMotors();
  }

  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();

}

void runMotors() {

  if (hallState1 == HIGH && hallState2 == LOW && bDown == false && cDown == false)
  {

    aDown = true;
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorSpeed);
    stepper1.moveTo(-300);
  }
  else if (hallState2 == HIGH && hallState1 == LOW && aDown == false  && cDown == false)
  {
    bDown = true;
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(-300);
  }
  else if (hallState1 == HIGH && hallState2 == HIGH && aDown == false && bDown == false) {
    cDown = true;
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(-300);
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorSpeed);
    stepper4.moveTo(-300);
  }
  else if (hallState1 == LOW && hallState2 == LOW && aDown == true) {
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorSpeed);
    stepper1.moveTo(300);
    if (stepper1.isRunning() == false) {
      Serial.println( "motor 1 is up");
      aDown = false;
    }
  }
  else if (hallState1 == LOW && hallState2 == LOW && bDown == true) {
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorSpeed);
    stepper2.moveTo(300);
    if (stepper2.isRunning() == false) {
      Serial.println( "motor 2 is up");
      bDown = false;
    }
  }
  else if (hallState1 == LOW && hallState2 == LOW && cDown == true) {
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorSpeed);
    stepper3.moveTo(300);

    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorSpeed);
    stepper4.moveTo(300);

    if (stepper3.isRunning() == false && stepper4.isRunning() == false) {
      Serial.println( "motor 3 and 4 is up");
      cDown = false;
    }
  }
}

void blink1() {

  hallState1 = !hallState1;
  checkTime = currentTime;

}

void blink2() {

  hallState2 = !hallState2;
  checkTime = currentTime;

}

void checkState() {
  int state1 = hallState1;
  int state2 = hallState2;
  // Serial.println("checkstate called");
  Serial.print(hallState1);
  Serial.print(", ");
  Serial.print(hallState2);
  Serial.println();
}



