

#include <Servo.h>


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 6;    // the number of the pushbutton pin
// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

Servo myservo9, myservo10, myservo11;

int pos = 180;    // variable to store the servo position

void setup() {
  myservo9.attach(4);  // attaches the servo on pin 9 to the servo object
  myservo10.attach(10);
  myservo11.attach(5);
  Serial.begin(9600);
}

void loop() {
  scene1();
  scene2();
  scene3();
  
}

void scene1() {
  int pos = 0;
  myservo9.write(pos);              // tell servo to go to position in variable 'pos'
  myservo10.write(pos);              // tell servo to go to position in variable 'pos'
  myservo11.write(pos);              // tell servo to go to position in variable 'pos'
  delay(5000);                       // waits 15ms for the servo to reach the position01
}

void scene2() {
  int pos = 10;
  for (pos = 10; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo9.write(pos);              // tell servo to go to position in variable 'pos'
    myservo10.write(pos);            // tell servo to go to position in variable 'pos'
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
}


void scene3() {
  int pos = 100;
  for (pos = 100; pos >= 10; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo9.write(pos);              // tell servo to go to position in variable 'pos'
    myservo10.write(pos);            // tell servo to go to position in variable 'pos'
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }

  delay(5000);
}


