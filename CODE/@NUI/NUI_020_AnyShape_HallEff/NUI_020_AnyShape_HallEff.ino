
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
}

void loop() {
  // read the state of the hall effect sensor:
  hallState1 = digitalRead(hallPin1);
  hallState2 = digitalRead(hallPin2);

  if (hallState1 == LOW) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
  }
  if (hallState2 == LOW) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
  }
  if (hallState1 == LOW && hallState2 == LOW) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
  }
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }
}
