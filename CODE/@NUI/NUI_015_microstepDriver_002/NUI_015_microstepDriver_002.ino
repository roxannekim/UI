
#include <StepperMSeries.h>

// change this to the number of steps on your motor
#define STEPS 200
#define PULSE_PIN 6
#define DIRECTION_PIN 7
#define ENABLE 27

StepperMSeries stepper(STEPS, PULSE_PIN, DIRECTION_PIN);

void setup() {
  // set the speed at 60 rpm:
  stepper.setSpeed(150);
  pinMode(ENABLE,OUTPUT);
  digitalWrite(ENABLE,HIGH);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  stepper.step(STEPS);
  delay(500);
  
   // step one revolution in the other direction:
  Serial.println("counterclockwise");
  stepper.step(-STEPS);
  delay(500); 
}
