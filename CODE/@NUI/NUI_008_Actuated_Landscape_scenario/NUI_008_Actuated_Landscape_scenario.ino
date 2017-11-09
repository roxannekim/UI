

#include <Servo.h>

Servo myservo9, myservo10, myservo11;

int pos = 180;
int scenes[] = {1, 2, 3};
int buttonPin = 6;

void setup() {
  pinMode(buttonPin, INPUT);
  myservo9.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo10.attach(10);
  myservo11.attach(11);
  Serial.begin(9600);


}

void loop() {
  int i = 0;

  if (buttonPin == 1) {
    i ++;
    scenes[i];

    Serial.println(i);
  }
}

void scene1() {
  int pos = 0;
  myservo9.write(pos);              // tell servo to go to position in variable 'pos'
  myservo10.write(pos);              // tell servo to go to position in variable 'pos'
  myservo11.write(pos);              // tell servo to go to position in variable 'pos'
  delay(1000);                       // waits 15ms for the servo to reach the position
}

void scene2() {
  int pos = 0;
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo9.write(pos);              // tell servo to go to position in variable 'pos'
    myservo10.write(pos / 2);            // tell servo to go to position in variable 'pos'
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
  }
  delay(1000);                       // waits 15ms for the servo to reach the position

}


void scene3() {
  int pos = 0;
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo9.write(pos);              // tell servo to go to position in variable 'pos'
    myservo10.write(pos / 2);            // tell servo to go to position in variable 'pos'
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
  }
  delay(1000);                       // waits 15ms for the servo to reach the position

}


