#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(256, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  colorWipe(10);

  autumn(100);
}

// Fill the dots one after the other with a color
void colorWipe( uint8_t wait) {
  for (int j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));

    }
    strip.show();
    delay(wait);
  }
}




//Theatre-style crawling lights with rainbow effect
void autumn(uint8_t wait) {
  for (int q = 0; q < 256; q++) {
    for (uint16_t i = 0; i < strip.numPixels(); i = i + 5) {
      strip.setPixelColor(i + q, strip.Color(255, abs(64 - q % 128), 0)); //turn every third pixel on
    }
    strip.show();
    delay(wait);

    for (uint16_t i = 0; i < strip.numPixels(); i = i + 5) {
      strip.setPixelColor(i + q, 0);      //turn every third pixel off

    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 128) {
    return strip.Color(0, 255 - WheelPos * 2, WheelPos * 2);
  }
  WheelPos -= 128;
  return strip.Color(0, WheelPos * 2, 255 - WheelPos * 2);
}

uint32_t WheelR(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 128) {
    return strip.Color(WheelPos * 2, 255 - WheelPos * 2, 0);
  }
  WheelPos -= 128;
  return strip.Color(255 - WheelPos * 2, WheelPos * 2,  0);
}

