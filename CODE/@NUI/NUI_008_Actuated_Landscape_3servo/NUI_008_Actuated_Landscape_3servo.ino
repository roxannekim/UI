
#include <Servo.h>


int button = 8;
int led = 13;
int status = false;
int pos = 0;

Servo myservo9, myservo10, myservo11;  // create servo object to control a servo


void setup() {
  pinMode(button, INPUT);

  myservo9.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo10.attach(10);
  myservo11.attach(11);

  Serial.begin(9600);
}

void loop() {
  //a) if the button is not pressed the false status is reversed by !status and the LED turns on
  //b) if the button is pressed the true status is reveresed by !status and the LED turns off

  myservo9.write(0);              // tell servo to go to position in variable 'pos'
  myservo10.write(0);              // tell servo to go to position in variable 'pos'
  myservo11.write(0);

  if (digitalRead(button) == true) {
    status = !status;
    switch (status) {
      case 1:
        Serial.println(status);
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo9.write(pos);              // tell servo to go to position in variable 'pos'
          myservo10.write(pos);              // tell servo to go to position in variable 'pos'
          myservo11.write(pos);              // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 15ms for the servo to reach the position

        }
        break;
      case 0:
        Serial.println(status);
        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
          myservo9.write(pos);              // tell servo to go to position in variable 'pos'
          myservo10.write(pos);              // tell servo to go to position in variable 'pos'
          myservo11.write(pos);              // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 15ms for the servo to reach the position
        }
        break;
    }
  } while (digitalRead(button) == true);
  delay(50); // keeps a small delay
}
