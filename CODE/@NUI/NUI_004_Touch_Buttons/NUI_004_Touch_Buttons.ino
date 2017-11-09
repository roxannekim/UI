#include <Adafruit_MPR121.h>

/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
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

void setup() {
  Serial.begin(9600);
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

}
