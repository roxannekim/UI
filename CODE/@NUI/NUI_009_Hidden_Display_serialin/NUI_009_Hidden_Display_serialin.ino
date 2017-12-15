#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#define FACTORYRESET_ENABLE     1

#define PIN                     6   // Which pin on the Arduino is connected to the NeoPixels?


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

float theY[] = {0, 1, 2, 3, 4, 5, 6, 7};
float theSpeeds[] = {0.8, 0.45, 1.8, 1, 1.25, 0.5, 1.1, .65};
float theX[] = {0, 0, 0, 0, 0, 0, 0, 0};

/*=========================================================================*/

const int  buttonPin = 2;    // the pin that the pushbutton is attached to

int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button



unsigned long millisSerial;        // milliseconds when Serial was received
bool bSerialActive = false;        // Serial data detected
bool bConnected = false;           // Serial connection (true or false based on timeout)
int wheelVal = 0;                  // value received from the wheel


void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  matrix.begin();
  matrix.setBrightness(100);
  matrix.fillScreen(0);
  matrix.show(); // This sends the updated pixel colors to the hardware.

  for ( int j = 0; j < 8; j++ ) {
    float currentSpeed = random(1, 400) / 100;
  }
}


void loop() {

  //particles();
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
  }
  else if (bConnected && (millis() - millisSerial > 500))
  {
    bSerialActive = false;    // wheel disconnected..
    bConnected = false;
    Serial.println("wheel disconnected!");
    buttonPushCounter = 0;
  }

  if (bConnected)
  {
    Serial.print("received: ");
    Serial.println(wheelVal);
    if (wheelVal > 128) arrow();
    else particles();

  }
  else {
    // read the pushbutton input pin:
    buttonState = digitalRead(buttonPin);

    if (buttonState != lastButtonState) {
      if (buttonState == HIGH) {
        buttonPushCounter++;
        if (buttonPushCounter > 2) buttonPushCounter = 0;
        Serial.println("on");
        Serial.print("number of button pushes:  ");
        Serial.println(buttonPushCounter);
      }
      lastButtonState = buttonState;
    }
    switch (buttonPushCounter) {
      case 0:
        waiting();
        break;
      case 1:
        arrow();
        break;
      case 2:
        particles();
        break;
      default:

        buttonPushCounter = buttonPushCounter % 3;
    }
  }//end else from if bConnected
}


void waiting() {
  matrix.fillScreen(0);

  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 4; i++) {
      matrix.drawFastHLine(j, 0, 32, matrix.Color(0, 0, 0)); // x0, y0, width, height
      matrix.show();
      delay(1);
    }
  }
}


void arrow() {

  matrix.fillScreen(0);

  for ( int j = 0; j < 33 ; j++) {
    for (int i = 0; i < 4; i ++) {
      matrix.drawFastHLine(i + j - 7,  i, 10, matrix.Color(0, pow(2, 4 + i),  pow(2, 5 + i))); // x0, y0, width, height
      //matrix.drawFastHLine(3 - i , 4 + i, 4, matrix.Color(0, pow(2, 7 - i),  pow(2, 8 - i))); // x0, y0, width, height
      matrix.drawFastHLine(i + j - 7,  i, 4, matrix.Color(0, 0, 0)); // x0, y0, width, height

    }

    for (int i = 0; i < 4; i ++) {
      matrix.drawFastHLine(- i + j - 4 , 4 + i, 10, matrix.Color(0, pow(2, 7 - i),  pow(2, 8 - i))); // x0, y0, width, height
      matrix.drawFastHLine(- i + j - 4 , 4 + i, 4, matrix.Color(0, 0, 0)); // x0, y0, width, height

    }

    matrix.show();
    delay(0);
  }


}

void particles() {

  matrix.fillScreen(0);

  for ( int j = 0; j < 8; j++ )
  {
    theX[j] = theSpeeds[j] + theX[j];

    if (theX[j] > 32 ) {
      theX[j] = 0;
    }
    matrix.drawPixel( theX[j], theY[j], matrix.Color( 255, 244, 229) );
  }
  matrix.show();
}





