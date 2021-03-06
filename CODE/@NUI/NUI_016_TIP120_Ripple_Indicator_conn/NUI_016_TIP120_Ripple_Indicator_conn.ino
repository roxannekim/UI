
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

unsigned long millisSerial;        // milliseconds when Serial was received
bool bSerialActive = false;        // Serial data detected
bool bConnected = false;           // Serial connection (true or false based on timeout)
int wheelVal = 0;

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

  if (Serial.available() > 0)
  {
    wheelVal = Serial.parseInt();

    bSerialActive = true;
    millisSerial = millis();
  }

  if (!bConnected && bSerialActive)
  {
    bConnected = true;        // wheel connected..
    Serial.println("wheel connected!");
    // autoSpeed();
    for (float i = 0; i < 360; i = i + 0.314) {
      //convert 0-360 angle to radian (needed for sin function)
      float rad = DEG_TO_RAD * i; //calculate sin of angle as number between 0 and 255
      int sinOut = constrain((sin(rad) * 128) + 128, 0, 255);
      analogWrite(dc, sinOut);
      delay(5);
    }
  }
  else if (bConnected && (millis() - millisSerial > 500))
  {
    bSerialActive = false;    // wheel disconnected..
    bConnected = false;
    Serial.println("wheel disconnected!");
    // manualSpeed();
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
  }
}


void autoSpeed() {
  for (float i = 0; i < 360; i = i + 0.314) {
    //convert 0-360 angle to radian (needed for sin function)
    float rad = DEG_TO_RAD * i; //calculate sin of angle as number between 0 and 255
    int sinOut = constrain((sin(rad) * 128) + 128, 0, 255);
    analogWrite(dc, sinOut);
    delay(5);
  }
}


void manualSpeed() {
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
}





