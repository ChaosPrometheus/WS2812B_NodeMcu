#include <Adafruit_NeoPixel.h>

#define LED_PIN     D4
#define LED_WIDTH   2
#define LED_HEIGHT  2
#define LED_COUNT   (LED_WIDTH * LED_HEIGHT)

Adafruit_NeoPixel matrix(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil(' '); // Read command until first space
    if (command == "/on") {
      int x = Serial.parseInt(); // Read x coordinate
      int y = Serial.parseInt(); // Read y coordinate
      int r = Serial.parseInt(); // Read red color intensity
      int g = Serial.parseInt(); // Read green color intensity
      int b = Serial.parseInt(); // Read blue color intensity
      int brightness = Serial.parseInt(); // Read brightness
      // Set color and brightness of the specified LED
      if (x >= 0 && x < LED_WIDTH && y >= 0 && y < LED_HEIGHT) {
        matrix.setPixelColor(y * LED_WIDTH + x, matrix.Color(r, g, b)); // Set color
        matrix.setBrightness(brightness); // Set brightness
        matrix.show();
      }
    } else if (command == "/off") {
      int x = Serial.parseInt(); // Read x coordinate
      int y = Serial.parseInt(); // Read y coordinate
      // Turn off the specified LED
      if (x >= 0 && x < LED_WIDTH && y >= 0 && y < LED_HEIGHT) {
        matrix.setPixelColor(y * LED_WIDTH + x, matrix.Color(0, 0, 0)); // Turn off LED
        matrix.show();
      }
    }
  }

  
}
