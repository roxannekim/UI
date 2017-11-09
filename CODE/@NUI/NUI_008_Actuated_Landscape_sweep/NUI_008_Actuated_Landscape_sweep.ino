/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo9, myservo10, myservo11;

int pos = 0;    // variable to store the servo position

void setup() {
  myservo9.attach(4);  // attaches the servo on pin 9 to the servo object
  myservo10.attach(5);
  myservo11.attach(11);
  Serial.begin(9600);
}

void loop() {

  myservo9.write(0);              // tell servo to go to position in variable 'pos'
  myservo10.write(0);              // tell servo to go to position in variable 'pos'
  myservo11.write(0);
  
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo9.write(pos);              // tell servo to go to position in variable 'pos'
    myservo10.write(pos/2);              // tell servo to go to position in variable 'pos'
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position

  }
  
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo9.write(pos);              // tell servo to go to position in variable 'pos'
    myservo10.write(pos/2);              // tell servo to go to position in variable 'pos'
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
    delay(50);                       // waits 15ms for the servo to reach the position
  }
}

