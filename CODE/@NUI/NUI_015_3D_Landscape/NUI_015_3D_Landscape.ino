#include <AccelStepper.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 9

#define NUM_LEDS 60

#define BRIGHTNESS 255

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

// Setup Motor
const int motorSpeed = 1000;
const int zeroSpeed = 500;
const int zeroAcceleration = 800;
const int motorAcceleration = 2000;

volatile AccelStepper stepperA(1, 6, 7); // (1 = stepper driver, 2 = pin# for step, 3 = pin# for direction)


volatile bool aDown = false; // Stepper 1
volatile bool aMoving = false;

int zeroing = false;
volatile int aZero = false;

const int aZeroOffset = -50;
const int aTop = -1200;

// Setup Limit Switches
const int limitPinA = 2;
volatile int limitStateA = LOW;

bool firstRun = true;
volatile bool lightsOn = false;
volatile bool raisePlatform = false;

const int buttonPin = 3;
int stageState = HIGH;         // the current stage of the output pin
int buttonState;
int lastButtonState = LOW;

volatile unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
const unsigned long debounceDelay = 250;    // the debounce time; increase if the output flickers

void setup()
{

  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(limitPinA, INPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPress, CHANGE);
  
  // Setup motor speed and acceleration
  stepperA.setMaxSpeed(zeroSpeed);
  stepperA.setAcceleration(zeroAcceleration);

  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  //if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop()
{
  /*
  int reading = digitalRead(buttonPin);

  
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        stageState = !stageState;
        Serial.println(stageState);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  */
  
  // Check limit switches
  limitStateA = digitalRead(limitPinA);

  // Serial.println(limitStateA);

  if ( firstRun == true )
  {
    Serial.println("======== First Run ========");
    zeroing = true;
    firstRun = false;
    delay(3000);// Warm up
    return;
  }
  else if ( zeroing == true ) {

    if ( limitStateA == LOW && aZero == false )
    {
      aZero = true;
      aMoving = false;
      stepperA.setCurrentPosition(0);
    }
    zeroMotors();
  }
  

  if ( aZero == true && zeroing == false ) { // If zeroing is complete

    if ( raisePlatform == false && lightsOn == true ) {

      Serial.println("Moving platform down, turning off lights");
      
      // turn off lights
      lightsOn = false;

      strip.begin();
      strip.setBrightness(0);
      strip.show(); // Initialize all pixels to 'off'
      
      strip.show();
      
      stepperA.moveTo(0);
      stepperA.run();
    }
    else if ( raisePlatform == true && stepperA.isRunning() == false && stepperA.currentPosition() == 0 ) { // condition to move up

      Serial.println("Raising the platform");
      stepperA.moveTo(aTop);
      stepperA.run();

    }
    else if ( stepperA.currentPosition() == aTop && raisePlatform == true && lightsOn == false ) {
      // we put code here to turn on the lights
      Serial.println("Platform raised, turning on lights");
      lightsOn = true;
      strip.setBrightness(BRIGHTNESS);
    }
  }

  if ( lightsOn == true )
  {
    Serial.println("Code that runs lights executed");
    whiteOverRainbow(10, 20, 4);
  }

  stepperA.run();



}

void zeroMotors() {


  if (limitStateA == LOW && aZero == false && aMoving == false)
  {
    Serial.println("Motor 1 Crashed");
    aZero = true;
    aMoving = false;
    stepperA.setCurrentPosition(0);
  }
  else if (aZero == false && aMoving == false) {
    Serial.println("A Moving to Zero");
    aMoving = true;
    stepperA.moveTo(10000);
  }
  else if (aZero == true && aMoving == false ) {
    Serial.println("A Moving back up");
    aMoving = true;
    stepperA.setSpeed(motorSpeed);
    stepperA.moveTo(aZeroOffset);
    stepperA.run();
    return;
  }
  else if (aZero == true && stepperA.distanceToGo() == 0) {
    Serial.println("A New Zero");
    aMoving = false;
    stepperA.setCurrentPosition(0);
    aZero = true;
    Serial.println("Zeroing complete");
    zeroing = false;
    return;
  }

}

void buttonPress() {

  unsigned long currentTime = millis();
  
  // Check debounce
  if (( currentTime - lastDebounceTime ) > debounceDelay) {
   lastDebounceTime = currentTime;
   raisePlatform = !raisePlatform;
  }
}


void whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {



  if (whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while (true) {

    //int light = analogRead(A0);
    int mapLight = 50;
    //Serial.println(mapLight);
    for (uint16_t i = 0; i < strip.numPixels(); i++) {

      if ((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ) {

        strip.setPixelColor(i, strip.Color(255, 255, 255, 0) );
      }

      else {
        strip.setPixelColor(i, strip.Color(4 * i, 240 - 4 * i, 30, 0)) ;
      }

    }
    if (millis() - lastTime > mapLight) {
      head++;
      tail++;
      if (head == strip.numPixels()) {
        loopNum++;
      }
      lastTime = millis();
    }

    if (loopNum == loops) return;

    head %= strip.numPixels();
    tail %= strip.numPixels();
    strip.show();
    delay(wait);
  }
}



