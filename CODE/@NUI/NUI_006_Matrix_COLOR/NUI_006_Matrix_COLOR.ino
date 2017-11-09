
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32 , 8, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

int x = matrix.width();
int y = matrix.height();


void setup() {
  matrix.begin();
  matrix.setBrightness(40);
}

void loop() {
  matrix.fillScreen(0);
  matrix.show();
  
  uint8_t r = 0, g = 0, b = 0;

  // Draw top half
  for (uint8_t x = 0; x < 32 ; x++) {
    for (uint8_t y = 0; y < 8; y++) {
      matrix.drawPixel(x, y, matrix.Color(r, g, b));
      r++;
      if (r == 8) {
        r = 0;
        g++;
        if (g == 8) {
          g = 0;
          b++;
        }
      }
    }
  }

  delay(100);
}
