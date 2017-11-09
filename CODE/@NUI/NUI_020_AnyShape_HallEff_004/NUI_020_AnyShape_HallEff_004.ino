#include <Servo.h>

//Defines
#define LINEAR100PIN 9        //Linear Actuator Digital Pin
#define LINEAR210PIN 10        //Linear Actuator Digital Pin

//max/min pulse values in microseconds for the linear actuators
#define LINEAR100_MIN      10  //
#define LINEAR100_MAX      5000 //
#define LINEAR210_MIN  10     //
#define LINEAR210_MAX  5000    //
#define MODE RISING

Servo LINEAR100, LINEAR210;

int linear100Value = 2500;   //current positional value being sent to the linear actuator.
int linear210Value = 2500;  //current positional value being sent to the linear actuator.

int speed = 10;

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

  //initialize servos
  LINEAR100.attach(LINEAR100PIN, LINEAR100_MIN, LINEAR100_MAX);      // attaches/activates the linear actuator as a servo object
  LINEAR210.attach(LINEAR210PIN, LINEAR210_MIN, LINEAR210_MAX);  // attaches/activates the linear actuator as a servo object

  //Analog pins do not need to be initialized

  //use the writeMicroseconds to set the linear actuators to their default positions
  LINEAR100.writeMicroseconds(2500);
  LINEAR210.writeMicroseconds(2500);

  //attachInterrupt(0, cup, RISING);
  //attachInterrupt(1, phone, RISING);

  Serial.begin(9600);
}

void loop() {
  hallState1 = digitalRead(hallPin1);
  hallState2 = digitalRead(hallPin2);

  if (hallState1 == HIGH && hallState2 == LOW) {
    attachInterrupt(0, CUP1, MODE);
    attachInterrupt(1, CUP1, MODE);
  }
  if (hallState1 == LOW && hallState2 == HIGH) {
    attachInterrupt(0, CUP2, MODE);
    attachInterrupt(1, CUP2, MODE);
  }

  if (hallState1 == HIGH && hallState2 == HIGH) {
    attachInterrupt(0, PHONE, MODE);
    attachInterrupt(1, PHONE, MODE);
  }
  if (hallState1 == LOW && hallState2 == LOW) {
    attachInterrupt(0, N, MODE);
    attachInterrupt(1, N, MODE);
  }
  //  else {
  //    attachInterrupt(0, NONE, RISING);
  //    attachInterrupt(1, NONE, RISING);
  //  }
}

void CUP1() {
  Serial.println("CUP1");
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  LINEAR100.writeMicroseconds(0);
  LINEAR210.writeMicroseconds(2500);

}

void CUP2() {
  Serial.println("CUP2");
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  LINEAR100.writeMicroseconds(2500);
  LINEAR210.writeMicroseconds(0);

}

void PHONE() {
  Serial.println("PHONE");
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  LINEAR100.writeMicroseconds(0);
  LINEAR210.writeMicroseconds(0);
}

void N() {
  Serial.println("N");
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  LINEAR100.writeMicroseconds(2500);
  LINEAR210.writeMicroseconds(2500);
}

void NONE() {
  Serial.println("NONE");
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  LINEAR100.writeMicroseconds(2500);
  LINEAR210.writeMicroseconds(2500);

}

