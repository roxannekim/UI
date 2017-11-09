/*********************************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  MIT license, check LICENSE for more information
  All text above, and the splash screen below must be included in
  any redistribution
*********************************************************************/
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#define FACTORYRESET_ENABLE     1

#define PIN                     6   // Which pin on the Arduino is connected to the NeoPixels?


byte smooth[] = {
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


// Example for NeoPixel 8x8 Matrix.  In this application we'd like to use it
// with the back text positioned along the bottom edge.
// When held that way, the first pixel is at the top left, and
// lines are arranged in columns, zigzag order.  The 8x8 matrix uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);
/*=========================================================================*/

void setup(void)
{
  matrix.begin();
  matrix.setBrightness(100);
  matrix.fillScreen(0);
  matrix.show(); // This sends the updated pixel colors to the hardware.


}

void loop(void) {
  rightTurn();
}

void rightTurn() {

  matrix.fillScreen(0);

  for ( int j = 0; j < 33 ; j++) {

    matrix.drawFastHLine( j, 1, 2, matrix.Color(255, 244, 229)); // x0, y0, width, heigh
    matrix.drawFastHLine( j, 1, 1, matrix.Color(0, 0, 0)); // x0, y0, width, height
    matrix.show();
    delay(1);
    matrix.drawFastHLine( j + 4, 2, 2, matrix.Color(255, 244, 229)); // x0, y0, width, heigh
    matrix.drawFastHLine( j + 4, 2, 1, matrix.Color(0, 0, 0)); // x0, y0, width, height
    matrix.show();
    delay(1);
    matrix.drawFastHLine( j + 3,  3, 2, matrix.Color(255, 244, 229)); // x0, y0, width, heigh
    matrix.drawFastHLine( j + 3,  3, 1, matrix.Color(0, 0, 0)); // x0, y0, width, height
    matrix.show();
    delay(1);
    matrix.drawFastHLine( j+7,  4, 2, matrix.Color(255, 244, 229)); // x0, y0, width, heigh
    matrix.drawFastHLine( j+7,  4, 1, matrix.Color(0, 0, 0)); // x0, y0, width, height
    matrix.show();
    delay(1);
  }

}

