// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      62

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second
int potPin = 0;    // select the input pin for the potentiometer
int ledPin = 9;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor
int mapVal = 0;
int oldVal = 1;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);
  Serial.println("HELLO");

  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);
}

void loop() {

  val = analogRead(potPin);    // read the value from the sensor
  //mapVal = map(val, 0, 1024, 0, 62);
  mapVal = map(val, 0, 900, 0, 62); 


  Serial.println(mapVal);

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

