#include <Adafruit_MPR121.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 7
#define NUM_LEDS 30
#define BRIGHTNESS 255

#define lightNum 3

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  Serial.begin(9600);

#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  pixels.setBrightness(255);
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(A0, INPUT);

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

    int buttonNumber = i;
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");

      for (uint16_t j = 0; j < lightNum; j++) {

        pixels.setPixelColor((11 -i)*lightNum + j, pixels.Color(0, 0, 0, 255)); //turn pixel on
      }
      pixels.show();
      delay(10);
    }

    // if it *was* touched and now *isnt*, alert!

    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");

      int buttonNumber = i;
      for (uint16_t j = 0; j < lightNum; j++) {
        pixels.setPixelColor((11 - i)*lightNum + j, pixels.Color(0, 0, 0, 0)); //turn pixel on
      }
      pixels.show();
      delay(10);

    }
  }

  // reset our state
  lasttouched = currtouched;
  return;
  delay(100);

}
