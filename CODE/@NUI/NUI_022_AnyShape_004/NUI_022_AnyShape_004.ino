#include <AccelStepper.h>


// Setup Motor
int motorSpeed = 2000;
int motorAcceleration = 1000;

volatile AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
volatile AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
volatile AccelStepper stepper3(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
volatile AccelStepper stepper4(1, 44, 46); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

volatile bool aDown = false; // Stepper 1
volatile bool aMoving = false;
volatile bool bDown = false; // Stepper 2
volatile bool bMoving = false;
volatile bool cDown = false; // Stepper 3 & 4
volatile bool cMoving = false;

volatile int zeroStage = 0; // Stage of progress for zeroing motors. 0 = 3 & 4, 1 = 1, 2 = 2;
int zeroing = false;
volatile int aZero = false;
volatile int bZero = false;
volatile int cZero = false;


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
volatile int checkTime = 0;
volatile int currentTime = 0;
int bounceBackDelay = 500; // ms
int limitBounceBackDelay = 250; //ms

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

  switch (zeroStage) {
    
    case 0: // Motors 3 & 4
    
      if (cZero == false && cMoving == false) { // Move motors down until we hit the limit switch
        cMoving = true;
        stepper3.moveTo(10000);
        stepper4.moveTo(10000);
        return;
      }
      else if (cZero == true && cMoving == false ) { // Move motors up to proper "0" after hitting swtich
        Serial.println("C Moving back up");
        cMoving = true;
        stepper3.setSpeed(motorSpeed);
        stepper4.setSpeed(motorSpeed);
        stepper3.moveTo(cZeroOffset);
        stepper4.moveTo(cZeroOffset);
        //delay(500);
        stepper3.run();
        stepper4.run();
        return;
      }
      else if (cZero == true && stepper3.distanceToGo() == 0) { // Set the new resting position as 0
        Serial.println("New Zero");
        cMoving = false;
        stepper3.setCurrentPosition(0);
        stepper4.setCurrentPosition(0);
        zeroStage++; // Move on to the next motor
        cZero = true;
        return;
      }
    
    break;

    case 1:
    
      if (aZero == false && aMoving == false) {
        Serial.println("A Moving to Zero");
        aMoving = true;
        stepper1.moveTo(10000);
      }
      else if (aZero == true && aMoving == false ) {
        Serial.println("A Moving back up");
        aMoving = true;
        stepper1.setSpeed(motorSpeed);
        stepper1.moveTo(aZeroOffset);
        //delay(500);
        stepper1.run();
        return;
      }
      else if (aZero == true && stepper1.distanceToGo() == 0) {
        Serial.println("A New Zero");
        aMoving = false;
        stepper1.setCurrentPosition(0);
        aZero = true;
        zeroStage++;
        return;
      }
      
    break;

    case 2:
      if (bZero == false && bMoving == false) {
        Serial.println("B Moving to Zero");
        stepper2.moveTo(10000);
        bMoving = true;
      }
      else if (bZero == true && bMoving == false ) {
        Serial.println("B Moving back up");
        bMoving = true;
        stepper2.setSpeed(motorSpeed);
        stepper2.moveTo(bZeroOffset);
        //delay(500);
        stepper2.run();
        return;
      }
      else if (bZero == true && stepper2.distanceToGo() == 0) {
        Serial.println("B New Zero");
        bMoving = false;
        stepper2.setCurrentPosition(0);
        bZero = true;
        zeroStage++;
        return;
      }

    break;

    case 3:
      Serial.println("Zeroing complete");
      zeroing = false;

    break;
  }
  
}

void limitDetectA() {
  currentTime = millis();
    
  if (currentTime - checkTime > limitBounceBackDelay) {
    checkTime = currentTime;
    
    if (aZero == false && zeroStage == 1 && aMoving == true) {
      aZero = true;
      aMoving = false;
      stepper1.setCurrentPosition(0);
    }
      
  }
}

void limitDetectB() {
  currentTime = millis();
  
  if (currentTime - checkTime > limitBounceBackDelay) {
    checkTime = currentTime;
    
    if (bZero == false && zeroStage == 2 && bMoving == true) {
      bZero = true;
      bMoving = false;
      stepper2.setCurrentPosition(0);
    }
      
  }
}

void limitDetectC() {
  
  currentTime = millis();
  
  if (currentTime - checkTime > limitBounceBackDelay) {
   
    checkTime = currentTime;
    
    if (cZero == false && zeroStage == 0 && cMoving == true) {
      cZero = true;
      cMoving = false;
      stepper3.setCurrentPosition(0);
      stepper4.setCurrentPosition(0);
    }
    
  }

}
