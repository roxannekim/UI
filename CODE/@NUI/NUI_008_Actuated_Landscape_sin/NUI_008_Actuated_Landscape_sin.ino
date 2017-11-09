
#include <Servo.h>

Servo myservo9, myservo10, myservo11;

int pos = 0;    // variable to store the servo position

void setup() {
  myservo9.attach(5);  // attaches the servo on pin 9 to the servo object
  myservo10.attach(10);
  myservo11.attach(11);
  Serial.begin(9600);
}

void loop() {

  myservo9.write(0);              // tell servo to go to position in variable 'pos'


  for (int i = 0; i <= 180; i ++) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo9.write(sin(i)*i);              // tell servo to go to position in variable 'pos'
    delay(50);

    if (i = 180) {
      i = 0;
    }
  }
}

