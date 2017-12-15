
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

#define dc 9
#define poten A0

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {

  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(dc, OUTPUT);
  pinMode(poten, INPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  int poten = analogRead(A0);
  int mapVal = map(poten, 200, 1024, 0, 255);
  if (poten <= 200) {
    mapVal = 0;
  } else {
    analogWrite(dc, mapVal);
    delay(5);
  }
  Serial.print(poten);
  Serial.print(" / ");
  Serial.println(mapVal);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}


void manualSpeed() {

}



