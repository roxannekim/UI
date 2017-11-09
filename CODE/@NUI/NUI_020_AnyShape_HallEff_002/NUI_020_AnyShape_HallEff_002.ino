#include <Servo.h>
Servo myservo1, myservo2 ;

int pos = 0;

const int hallPin1 = 2;
const int hallPin2 = 3;
const int ledPin1 =  6;
const int ledPin2 =  7;
int hallState1 = 0;
int hallState2 = 0;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(hallPin1, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(hallPin2, INPUT);

  myservo1.attach(4);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(5);;

  myservo1.write(0);
  myservo2.write(0);

  Serial.begin(9600);
}

void loop() {
  // read the state of the hall effect sensor:
  hallState1 = digitalRead(hallPin1);
  hallState2 = digitalRead(hallPin2);

  Serial.print(hallState1);
  Serial.print(" / ");
  Serial.println(hallState2);

  if (hallState1 == LOW && hallState2 == HIGH) {
    digitalWrite(ledPin1, HIGH);
    //  myservo1.write(180);
    digitalWrite(ledPin2, LOW);
    //    myservo2.write(0);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo1.write(pos);              // tell servo to go to position in variable 'pos'
      delay(50);                       // waits 15ms for the servo to reach the position

    }
  }
  if (hallState2 == LOW && hallState1 == HIGH) {
    digitalWrite(ledPin1, LOW);
    myservo1.write(0);
    digitalWrite(ledPin2, HIGH);
    myservo2.write(180);
    delay(50);
  }
  if (hallState1 == LOW && hallState2 == LOW) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    myservo1.write(180);
    myservo2.write(180);
    delay(50);
  }

  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    myservo1.write(0);
    myservo2.write(0);
    delay(50);
  }
}
