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
#define NUMPIXELS      24

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second
int potPin = A0;    // select the input pin for the potentiometer
int ledPin = 9;   // select the pin for the LED
int val = 0;       // variable to store the value coming from the sensor
int mapVal = 0;
int easedVal = 0;
int oldVal = 1;

double marktime = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin();
  pixels.show();
  pixels.setBrightness(255);
  //Serial.println("HELLO");

  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);
  //Serial.begin(115200);
}

void loop() {

  val = analogRead(A0);    // read the value from the sensor

  //easedVal = (1+sin((mapVal-12)/8))*124 ;

  if (val < 500) {
    val = 0;
    mapVal = 0;
    easedVal = 0;
    theaterChase(pixels.Color(0,0,0), 0, easedVal);
  } else if ( val >= 500 && val < 800) {
    mapVal = map(val, 500, 800, 0,24);
    easedVal = mapVal;
    theaterChase(pixels.Color(easedVal * 9, 255 - 5 * easedVal, 0), 0, easedVal);
  } else if ( val >= 800) {
    mapVal = 24;
    easedVal = mapVal;
  }

  /*
      easeOutInQuad

      static public function easeOutInQuad(t:Number, b:Number, c:Number, d:Number, p_params:Object):Number
      Easing equation function for a quadratic (t^2) easing out/in: deceleration until halfway, then acceleration

      Parameters

      t Number  Current time (in frames or seconds)
      b Number  Starting value
      c Number  Change needed in value
      d Number  Expected easing duration (in frames or seconds)
      Return

      Number  The correct value

          public static function easeOutInQuad (t:Number, b:Number, c:Number, d:Number, p_params:Object = null):Number {
        if (t < d/2) return easeOutQuad (t*2, b, c/2, d, p_params);
        return easeInQuad((t*2)-d, b+c/2, c/2, d, p_params);

      easeInOutQuad:function(x,t,b,c,d){
      if((t/=d/2)<1)returnc/2*t*t+b;
      return-c/2*((--t)*(t-2)-1)+b;

  */
  delay(25);
  double curtime = millis();
  if (curtime-marktime > 500) {
    Serial.println( map(val, 0, 1023, 0, 255) );
    marktime = millis();
  }

  /*
  //Serial.print(val);
  //Serial.print("  /  ");
  //Serial.println(easedVal);
  Serial.println( map(val, 0, 1023, 0, 255) );
  delay(500);
  */

}

void theaterChase(uint32_t c, uint8_t wait, uint8_t p) {

  for (uint16_t i = 0; i < p; i++) {
    pixels.setPixelColor(i, c);  //turn pixel on
  }
  for (uint16_t i = p; i < 26; i++) {
    pixels.setPixelColor(i , 0);
  }
  pixels.show();
  delay(wait);
}

