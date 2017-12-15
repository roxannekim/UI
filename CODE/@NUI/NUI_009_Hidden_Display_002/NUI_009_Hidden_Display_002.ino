#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#define FACTORYRESET_ENABLE     1

#define PIN                     6   // Which pin on the Arduino is connected to the NeoPixels?

// Define matrix width and height.
#define mw 32
#define mh 8

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(mw, mh, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

float theY[] = {0, 1, 2, 3, 4, 5, 6, 7};
float theSpeeds[] = {0.8, 0.45, 1.8, 1, 1.25, 0.5, 1.1, .65};
float theX[] = {0, 0, 0, 0, 0, 0, 0, 0};
int interval[] = {0, 40, 80, 120, 150, 180, 200, 220, 230, 240, 250, 260};
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
  manual();

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

  if (bConnected && (millis() - millisSerial > 500))
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
    if (wheelVal > 128) {
      arrow_progress1();
      arrow_progress2();
    }
    else {
      particles();
    }
  }

  else {
    manual();
  }
}//end else from if bConnected


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


void arrow_progress1() {

  matrix.fillScreen(0);

  for (int j = - 32; j < 1 ; j ++) {
    for (int i = 0; i < 33; i ++) {
      int c = matrix.Color(52 + i, 31 + 7 * i, 255 - 7 * i);
      if (i < 28) {
        matrix.drawRect(j + i, 0, 1, 8, c);
      }
      if (i >= 29) {
        int k = i - 29;
        matrix.drawRect(28 + k + j, k, 1, 2 * (4 - k), c);
      }
    }
    matrix.show();
    delay(0);
  }

  for (int j = - 32; j < -4 ; j ++) {
    for (int i = 0; i < 33; i ++) {
      int c = matrix.Color(0, 0, 0);
      if (i < 28) {
        matrix.drawRect(j + i, 0, 1, 8, c);
      }
      if (i >= 29) {
        int k = i - 29;
        matrix.drawRect(28 + k + j, k, 1, 2 * (4 - k), c);
      }
    }
    matrix.show();
    delay(0);
  }

  for ( int m = 0; m < 200 ; m ++) {
    float n = m / 2;
    float c = matrix.Color(120 + 2 * n, 200 - 2 * n, 31 - n / 2);
    int c0 = matrix.Color(0, 0, 0);

    for (int i = 0; i < 4; i ++) {
      matrix.drawFastHLine(i + m - 7,  i, 10, c); // x0, y0, width, height
      matrix.drawFastHLine(i + m - 7,  i, 5, c0); // x0, y0, width, height

      matrix.drawFastHLine(i + m - 17,  i, 10, c);
      matrix.drawFastHLine(i + m - 17,  i, 5, 0);

      matrix.drawFastHLine(i + m - 29,  i, 10, c);
      matrix.drawFastHLine(i + m - 29,  i, 5, 0);

      matrix.drawFastHLine(i + m - 43,  i, 10, c);
      matrix.drawFastHLine(i + m - 43,  i, 5, 0);

      matrix.drawFastHLine(i + m - 59,  i, 10, c);
      matrix.drawFastHLine(i + m - 59,  i, 5, 0);

      matrix.drawFastHLine(i + m - 77,  i, 10, c);
      matrix.drawFastHLine(i + m - 77,  i, 5, 0);

      matrix.drawFastHLine(i + m - 97,  i, 10, c);
      matrix.drawFastHLine(i + m - 97,  i, 5, 0);
    }

    for (int i = 0; i < 4; i ++) {

      matrix.drawFastHLine(- i + m - 4 , 4 + i, 10, c); // x0, y0, width, height
      matrix.drawFastHLine(- i + m - 4 , 4 + i, 5, 0); // x0, y0, width, height

      matrix.drawFastHLine(- i + m - 14 , 4 + i, 10, c);
      matrix.drawFastHLine(- i + m - 14 , 4 + i, 5, 0);

      matrix.drawFastHLine(- i + m - 26 , 4 + i, 10, c);
      matrix.drawFastHLine(- i + m - 26 , 4 + i, 5, 0);

      matrix.drawFastHLine(- i + m - 40 , 4 + i, 10, c);
      matrix.drawFastHLine(- i + m - 40 , 4 + i, 5, 0);

      matrix.drawFastHLine(- i + m - 56 , 4 + i, 10, c);
      matrix.drawFastHLine(- i + m - 56 , 4 + i, 5, 0);

      matrix.drawFastHLine(- i + m - 74 , 4 + i, 10, c);
      matrix.drawFastHLine(- i + m - 74 , 4 + i, 5, 0);

      matrix.drawFastHLine(- i + m - 94 , 4 + i, 10, c);
      matrix.drawFastHLine(- i + m - 94 , 4 + i, 5, 0);

    }
    matrix.show();
  }
}


void arrow_progress2() {

  // Ready, Get, Set, Go!

  for (int i = 0; i < 255 ; i++) {
    matrix.fillScreen(matrix.Color(255, 0, 0));
    matrix.show();
  }

  for (int i = 32; i > 0 ; i--) {
    matrix.fillCircle(mw / 2, mh / 2, i / 2 + 2, matrix.Color(8 * i - 1, 128 - 4 * i, 32 - i));
    matrix.show();
    delay(50);
  }


  for (int i = 0; i < 15; i++) {
    for (int j = 4; j > 0;  j--) {
      matrix.drawFastHLine(0, 4 - j, i + j - 1, matrix.Color(0, 0, 0));
      matrix.drawFastHLine(0, 3 + j, i + j - 1, matrix.Color(0, 0, 0));
      matrix.drawFastHLine(32 - i + j, 4 - j, i + j, matrix.Color(0, 0, 0));
      matrix.drawFastHLine(32 - i + j, 3 + j, i + j, matrix.Color(0, 0, 0));
    }
    matrix.show();
    delay(50);
  }


  for ( int m = 0; m < 300 ; m ++) {
    float n = m / 2;
    float c = matrix.Color(0, 255, 60);
    int c0 = matrix.Color(0, 0, 0);

    for (int i = 0; i < 4; i ++) {
      for (int j = 0; j < 13; j++)   {
        matrix.drawFastHLine(14 + interval[j] - i - m,  i, 10, c); // x0, y0, width, height
        matrix.drawFastHLine(19 + interval[j] - i - m,  i, 5, c0); // x0, y0, width, heigh
      }
    }

    for (int i = 0; i < 4; i ++) {
      for (int j = 0; j < 13; j++)   {
        matrix.drawFastHLine(11 + interval[j] + i - m , 4 + i, 10, c); // x0, y0, width, height
        matrix.drawFastHLine(16 + interval[j] + i - m,  4 + i, 5, c0); // x0, y0, width, height
      }
    }
    matrix.show();
  }
}


void particles() {

  //matrix.fillScreen(0);

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


void manual() {

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
      arrow_progress1();
      arrow_progress2();
      break;
    case 2:
      particles();
      break;
    default:

      buttonPushCounter = buttonPushCounter % 3;
  }
}


