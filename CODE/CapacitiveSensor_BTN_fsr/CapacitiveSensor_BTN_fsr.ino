#include <Adafruit_NeoPixel.h>
#include <Adafruit_MPR121.h>
#include <Wire.h>

#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            3
#define NUMPIXELS      62

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_MPR121 cap = Adafruit_MPR121();
// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
int pin12 = 12;
int pin11 = 11;
int pin10 = 10;
int pin9 = 9;
int pin8 = 8;
int pin7 = 7;
int pin6 = 6;
int pin5 = 5;

int delayval = 10; // delay for half a second
int potPin = 0;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor
int mapVal = 0;
int oldVal = 1;

void setup() {
  Serial.begin(9600);

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);

  pinMode(pin12, OUTPUT);
  pinMode(pin11, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin5, OUTPUT);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

}

void loop() {
  // Get the currently touched pads
  currtouched = cap.touched();

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");

      int buttonNumber = i;
      switch (buttonNumber) {
        case 11:
          digitalWrite(pin12, HIGH);
          break;
        case 10:
          digitalWrite(pin11, HIGH);
          break;
        case 9:
          digitalWrite(pin10, HIGH);
          break;
        case 8:
          digitalWrite(pin9, HIGH);
          break;
        case 7:
          digitalWrite(pin8, HIGH);
          break;
        case 6:
          digitalWrite(pin7, HIGH);
          break;
        case 5:
          digitalWrite(pin6, HIGH);
          break;
        case 4:
          digitalWrite(pin5, HIGH);
          break;
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      int buttonNumber = i;

      switch (buttonNumber) {
        case 11:
          digitalWrite(pin12, LOW);
          break;
        case 10:
          digitalWrite(pin11, LOW);
          break;
        case 9:
          digitalWrite(pin10, LOW);
          break;
        case 8:
          digitalWrite(pin9, LOW);
          break;
        case 7:
          digitalWrite(pin8, LOW);
          break;
        case 6:
          digitalWrite(pin7, LOW);
          break;
        case 5:
          digitalWrite(pin6, LOW);
          break;
        case 4:
          digitalWrite(pin5, LOW);
          break;
      }
    }
  }
  // reset our state
  lasttouched = currtouched;
  return;
  delay(100);

  val = analogRead(potPin);    // read the value from the sensor
  mapVal = map(val, 0, 900, 0, 62);
  theaterChase(pixels.Color(mapVal * 2, 124 - 2 * mapVal, 0), 10, mapVal);

}


void theaterChase(uint32_t c, uint8_t wait, uint8_t mapVal) {

  for (uint16_t i = 0; i < mapVal; i++) {
    pixels.setPixelColor(i, c);  //turn pixel on
  }
  for (uint16_t i = mapVal; i < 62; i++) {
    pixels.setPixelColor(i , 0);
  }
  pixels.show();
  delay(wait);
}
