
#include <Servo.h>

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
// Variables will change:
int ledState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
Servo myservo9, myservo10, myservo11;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val, val1, val2;    // variable to read the value from the analog pin


void setup() {
  pinMode(buttonPin, INPUT);

  myservo9.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo10.attach(10);
  myservo11.attach(11);
  Serial.begin(9600);

}

void loop() {

  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }


    switch (ledState) {
      case 0:
        val = 0;
        Serial.println(val);
        myservo9.write(val);
        myservo10.write(val);
        myservo11.write(val);
        delay(15);
        break;
      case 1:
        val = 180;
        Serial.println(val);
        myservo9.write(val);
        myservo10.write(val);
        myservo11.write(val);
        delay(15);
        break;
    }
    lastButtonState = reading;
  }

}
