

#include <Adafruit_NeoPixel.h>

#include <SPI.h>
#include <WiFi.h>


#define USE_SERIAL Serial
#define BRIGHTNESS 255
const int numPixels  = 64;
const int ledPin = 14; // the pin that the LED is attached to
float speed ;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, ledPin, NEO_GRB + NEO_KHZ800);

ESP8266WiFiMulti WiFiMulti;

const size_t bufferSize = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3) + 60;
DynamicJsonBuffer jsonBuffer(bufferSize);

void setup() {

  USE_SERIAL.begin(115200);
  // USE_SERIAL.setDebugOutput(true);

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFiMulti.addAP("RHK", "11223344");

  pinMode(ledPin, OUTPUT);


}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    //callWeatherAPI("New York");
    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
    http.begin("http://api.wunderground.com/api/3e5efec846df6775/conditions/q/NY/10003.json");

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        USE_SERIAL.println(payload);

        JsonObject& root = jsonBuffer.parseObject(payload);
        long speed = root["current_observation"]["wind_mph"]; // 1351824120

        Serial.println(speed);

      } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }

    dayWhite(10, 5 + speed * 10);
    //delay(100);
  }
}



void dayWhite(uint8_t wait, uint8_t mapSpeed) {
  for (int j = 0; j < 256 ; j++) {
    for (uint16_t i = 0; i < strip.numPixels() +  mapSpeed ; i++) {
      strip.setBrightness(mapSpeed - abs(mapSpeed - j % mapSpeed * 2));
      strip.setPixelColor(j, 100, 250, 150);
      Serial.println(mapSpeed - abs(mapSpeed - j % mapSpeed * 2));
    }
    delay(wait);
    strip.show();
  }
}

