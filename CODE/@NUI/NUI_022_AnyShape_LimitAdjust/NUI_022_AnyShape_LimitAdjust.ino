#include <AccelStepper.h>


// Setup Motor
int motorSpeed = 2000;
int motorAcceleration = 1000;

AccelStepper stepper1(1, 11, 12); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper2(1, 9, 10); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper3(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)
AccelStepper stepper4(1, 44, 46); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)

// Serial??
volatile byte STATE = LOW;
volatile byte TRANSITION = LOW;

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
int limitBounceBackDelay = 250; //ms

int currentMotor = 0;
int manualStepAmount = 50;

void setup() {
    
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

  stepper1.run();
  stepper2.run();
  stepper3.run();
  stepper4.run();
}


void limitDetectA() {
  currentTime = millis();
    
  if (currentTime - checkTime > limitBounceBackDelay) {
    Serial.println("Limit A");
    checkTime = currentTime;
    
     if ( currentMotor == 0 ) {
      stepper3.moveTo( stepper3.currentPosition() + manualStepAmount );
      stepper4.moveTo( stepper4.currentPosition() + manualStepAmount );
    }
    else if (currentMotor == 1) {
      stepper1.moveTo( stepper1.currentPosition() + manualStepAmount );
    }
    else if (currentMotor == 2) {
      stepper2.moveTo( stepper2.currentPosition() + manualStepAmount );
    } 
      
  }
}

void limitDetectB() {
  currentTime = millis();
  
  if (currentTime - checkTime > limitBounceBackDelay) {
    Serial.println("Limit B");
    checkTime = currentTime;
    
    if ( currentMotor == 0 ) {
      stepper3.moveTo( stepper3.currentPosition() - manualStepAmount );
      stepper4.moveTo( stepper4.currentPosition() - manualStepAmount );
    }
    else if (currentMotor == 1) {
      stepper1.moveTo( stepper1.currentPosition() - manualStepAmount );
    }
    else if (currentMotor == 2) {
      stepper2.moveTo( stepper2.currentPosition() - manualStepAmount );
    }
      
  }
}

void limitDetectC() {
  currentTime = millis();
  
  if (currentTime - checkTime > limitBounceBackDelay) {
    Serial.println("Limit C");
    Serial.println(currentTime - checkTime);
    checkTime = currentTime;

    currentMotor ++;

    if (currentMotor > 2) {
      currentMotor = 0;
    }
    
  }

}
