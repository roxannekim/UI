#include <Adafruit_MPR121.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 7
#define NUM_LEDS 15
#define BRIGHTNESS 255

#define lightNum 3

byte neopix_gamma[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

byte dingdong [5][3] = {{0, 3, 13}, {1, 6, 10}, {5, 9, 14}, {4, 8, 12}, {2, 7, 11}};


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
    //delay(10);
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
      //Serial.print(i); Serial.println(" touched");
      for (int k = 0; k < 256 ; k++) {
        for (uint16_t j = 0; j < lightNum ; j++) {
          pixels.setPixelColor(dingdong[i - 7][j], pixels.Color(0, 0, 0, neopix_gamma[k])); //turn pixel on

        }
        pixels.show();
        if ((currtouched & _BV(7)) && (currtouched & _BV(8)) && (currtouched & _BV(9)) && (currtouched & _BV(10)) && (currtouched & _BV(11))) {
          for (uint16_t j = 0; j < 15 ; j++) {
            pixels.setPixelColor(j, pixels.Color(15 * j, 0, 255 - j * 15, 0)); //turn pixel on
            //pixels.setPixelColor(j, pixels.Color(0, 0, 0, abs(250-j*50))); //turn pixel on
          }
        }
        pixels.show();
      }
    }


    // if it *was* touched and now *isnt*, alert!

    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" released");

      int buttonNumber = i;
      for (int k = 255; k >= 0 ; k--) {
        for (uint16_t j = 0; j < lightNum; j++) {
          pixels.setPixelColor(dingdong[i - 7][j], pixels.Color(0, 0, 0, neopix_gamma[k])); //turn pixel on
        }
        pixels.show();

        if ((currtouched & _BV(7)) && (currtouched & _BV(8)) && (currtouched & _BV(9)) && (currtouched & _BV(10)) && (currtouched & _BV(11))) {
          for (uint16_t j = 0; j < 15 ; j++) {
            pixels.setPixelColor(j, pixels.Color(15 * j, 0, 255 - j * 15, 0)); //turn pixel on
          }
        }
        pixels.show();
      }
    }
  }

  // reset our state
  lasttouched = currtouched;
  return;

}
