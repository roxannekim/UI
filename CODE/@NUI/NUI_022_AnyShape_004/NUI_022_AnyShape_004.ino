#include <AccelStepper.h>


// Setup Motor
int motorSpeed = 2000;
int motorAcceleration = 1000;

AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper3(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper4(1, 44, 46); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

bool aDown = false; // Stepper 1
bool bDown = false; // Stepper 2
bool cDown = false; // Stepper 3 & 4

int zeroStage = 0; // Stage of progress for zeroing motors. 0 = 3 & 4, 1 = 1, 2 = 2;
int zeroing = false;
int aZero = false;
int bZero = false;
int cZero = false;

int aZeroOffset = -1000;
int bZeroOffset = -1000;
int cZeroOffset = -400;

// Serial??
volatile byte STATE = LOW;
volatile byte TRANSITION = LOW;

// Setup Hall sensors
const int hallPin1 = 2;
int hallState1 = LOW;
const int hallPin2 = 3;
int hallState2 = LOW;

// Setup Limit Switches
int limitPinA = 19;
int limitStateA = LOW;
int limitPinB = 20;
int limitStateB = LOW;
int limitPinC = 21;
int limitStateC = LOW;

// Event listener bounceback prevention
int checkTime = 0;
int currentTime = 0;
int bounceBackDelay = 500; // ms

bool firstRun = true;

void setup() {

  // Setup object detection
  pinMode(hallPin1, INPUT_PULLUP);
  pinMode(hallPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallPin1), blink1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(hallPin2), blink2, CHANGE);
  
  
  // Setup motor speed and acceleration
  stepper1.setSpeed(motorSpeed);
  stepper1.setAcceleration(motorAcceleration);
  stepper2.setSpeed(motorSpeed);
  stepper2.setAcceleration(motorAcceleration);
  stepper3.setSpeed(motorSpeed);
  stepper3.setAcceleration(motorAcceleration);
  stepper4.setSpeed(motorSpeed);
  stepper4.setAcceleration(motorAcceleration);

  // Setup limit listeners
  attachInterrupt( digitalPinToInterrupt( limitPinA ), limitDetectA, RISING);
  attachInterrupt( digitalPinToInterrupt( limitPinB ), limitDetectB, RISING);
  attachInterrupt( digitalPinToInterrupt( limitPinC ), limitDetectC, RISING);
  
  Serial.begin(9600);
  
}


void loop() {

  
  currentTime = millis();

  if (firstRun) {
    Serial.println("======== First Run ========");
    zeroing = true;
    firstRun = false;
    return;
  }
  else if (zeroing)
  {
    //Serial.println("Zeroing...");
    zeroMotors();
  }
  // Check if any motors are currently running, and if bounceback time has passed
  else if (!stepper1.isRunning() && !stepper2.isRunning() && !stepper3.isRunning() && !stepper4.isRunning() && currentTime - checkTime > bounceBackDelay ) {
    //Serial.println("No motors running");
    //checkState();
    setMotors();
  }
  
  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();

}

void setMotors() {

  if (hallState1 == HIGH && hallState2 == LOW && bDown == false && cDown == false)
  {

    aDown = true;
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorAcceleration);
    stepper1.moveTo(-300);
  }
  else if (hallState2 == HIGH && hallState1 == LOW && aDown == false  && cDown == false)
  {
    bDown = true;
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorAcceleration);
    stepper2.moveTo(-300);
  }
  else if (hallState1 == HIGH && hallState2 == HIGH && aDown == false && bDown == false) {
    cDown = true;
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorAcceleration);
    stepper3.moveTo(-300);
    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorAcceleration);
    stepper4.moveTo(-300);
  }
  else if (hallState1 == LOW && hallState2 == LOW && aDown == true) {
    stepper1.setMaxSpeed(motorSpeed);
    stepper1.setAcceleration(motorAcceleration);
    stepper1.moveTo(300);
    if (stepper1.isRunning() == false) {
      Serial.println( "motor 1 is up");
      aDown = false;
    }
  }
  else if (hallState1 == LOW && hallState2 == LOW && bDown == true) {
    stepper2.setMaxSpeed(motorSpeed);
    stepper2.setAcceleration(motorAcceleration);
    stepper2.moveTo(300);
    if (stepper2.isRunning() == false) {
      Serial.println( "motor 2 is up");
      bDown = false;
    }
  }
  else if (hallState1 == LOW && hallState2 == LOW && cDown == true) {
    stepper3.setMaxSpeed(motorSpeed);
    stepper3.setAcceleration(motorAcceleration);
    stepper3.moveTo(300);

    stepper4.setMaxSpeed(motorSpeed);
    stepper4.setAcceleration(motorAcceleration);
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

void zeroMotors() {
  if (zeroStage == 0 && cZero == false) {
    // Move motors down until we hit the limit switch
    stepper3.moveTo(10000);
    stepper4.moveTo(10000);
    return;
  }
  else if (zeroStage == 0 && cZero == true && !stepper3.isRunning() ) {
    // Move motor up to proper "0"
   
    Serial.println(stepper3.currentPosition());

    Serial.println("Moving back up");
    stepper3.setSpeed(motorSpeed);
    stepper4.setSpeed(motorSpeed);
    stepper3.moveTo(cZeroOffset);
    stepper4.moveTo(cZeroOffset);
    delay(500);
    stepper3.run();
    stepper4.run();
    return;
  }
  else if (zeroStage == 0 && cZero == true && stepper3.distanceToGo() == 0) {
    Serial.println("New Zero");
    stepper3.setCurrentPosition(0);
    stepper4.setCurrentPosition(0);
    zeroStage++;
    cZero = true;
    return;
  }
  else if (zeroStage == 2 && aZero == false) {
    stepper1.moveTo(10000);
  }
  else if (zeroStage == 4 && bZero == false) {
    stepper2.moveTo(10000);
  }
  else if (zeroStage == 3) {
    Serial.println("Zeroing complete");
    zeroing = false;
  }
  
}

void limitDetectA() {
  Serial.println("Limit A");
  if (aZero == false && zeroStage == 3) {
    stepper1.setCurrentPosition(0);
    aZero = true;
    zeroStage++;
  }
}
void limitDetectB() {
  Serial.println("Limit B");
  if (bZero == false && zeroStage == 6) {
    stepper2.setCurrentPosition(0);
    bZero = true;
    zeroStage++;
  }  
}
void limitDetectC() {
  Serial.println("Limit C");
  if (cZero == false && zeroStage == 0) {
    //Serial.println("Set temp limit");
    //Serial.println(stepper3.currentPosition());
    stepper3.setCurrentPosition(0);
    stepper4.setCurrentPosition(0);
    cZero = true;
    //zeroStage++;
  }
}
