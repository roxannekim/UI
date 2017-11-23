int maxPressure = 800; // Maximum FSR reading until compessor is shut off

int compressorPin = 9; // PWM Pin 9 connected to the base of the transistor
int solenoidPin = 11; // PWM Pin 11 connected to the base of the transistor
int led = 13; // Built in Arduino LED
int buttonPin = 2; //Needs to be an interrupt pin
int fsrAnalogPin = 0; // Pin to read pressure level

bool inflated = false;
bool inflating = false;
bool deflating = false;
bool firstRun = true;

int fsrReading; //Variable that holds the FSR value
int lastInterruptTime = 0; //Last time interrupt was called
int debounceDelay = 500; // Minimum amount of time that needs to pass for next interrupt

void setup() {
  Serial.begin(9600);
  // set the transistor pin as output:
  pinMode(compressorPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  analogWrite(solenoidPin, 255); // Close solenoid
  analogWrite(compressorPin, 0); // Turn off compressor

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, RISING); // Event listener for button

}

void loop() {

  fsrReading = analogRead(fsrAnalogPin); // Store pressure reading

  checkInflation();

}

void checkInflation() {

  // If we have reached our pressure threashold and are currently inflating
  if (inflating == true && fsrReading > maxPressure) {

    inflating = false;
    inflated = true;

    digitalWrite(compressorPin, 0); // Shut off compressor

    Serial.println("Max pressure reached, compressor off...");
    //delay(5000);
    //deflate();

  } else if (deflating == true && fsrReading < 50) {
    deflating = false;
    inflated = false;

    digitalWrite(led, LOW);
    //digitalWrite(solenoidPin, 255);

    Serial.println("Deflation complete!");
  }
}

void inflate() {
  Serial.println("Inflating");
  digitalWrite(solenoidPin, 255); // Make sure solenoid is closed
  digitalWrite(led, LOW);
  digitalWrite(compressorPin, 255); // Turn on compressor
  inflating = true;

}

void deflate() {
  Serial.println("Deflating!");
  digitalWrite(solenoidPin, 0); // Open the solenoid
  digitalWrite(compressorPin, 0); // Make sure compressor is off
  digitalWrite(led, HIGH);
  deflating = true;

}

void buttonPress() {
  
  int currentTime = millis(); // Store the current time

  if (currentTime - lastInterruptTime > debounceDelay) { // Make sure enough time has passed to prevent bounce
    
    lastInterruptTime = currentTime; // Update last interrupt

    Serial.println("Button Press");

    if (inflating == false && deflating == false && inflated == false) {
      inflate();
    } else if (inflating == false && deflating == false && inflated == true) {
      deflate();
    }

  }
}
