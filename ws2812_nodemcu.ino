#include <Adafruit_NeoPixel.h>

#define LED_PIN     D4
#define LED_WIDTH   42
#define LED_HEIGHT  8
#define LED_COUNT   (LED_WIDTH * LED_HEIGHT)

Adafruit_NeoPixel matrix(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int getPixelIndex(int x, int y) {
  x -= 1;
  y -= 1;
  if (y % 2 == 0) {
    return y * LED_WIDTH + x;
  } else {
    return y * LED_WIDTH + (LED_WIDTH - 1 - x);
  }
}

void setup() {
  Serial.begin(9600);
  matrix.begin();
  matrix.show(); 
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil(' '); 
    if (command == "/on") {
      int x = Serial.parseInt(); 
      int y = Serial.parseInt(); 
      int r = Serial.parseInt();
      int g = Serial.parseInt(); 
      int b = Serial.parseInt(); 
      int brightness = Serial.parseInt();
      if (x > 0 && x <= LED_WIDTH && y > 0 && y <= LED_HEIGHT) {
        matrix.setPixelColor(getPixelIndex(x, y), matrix.Color(r, g, b));
        matrix.setBrightness(brightness); 
        matrix.show();
      }
    } else if (command == "/off") {
      int x = Serial.parseInt(); 
      int y = Serial.parseInt(); 
      if (x > 0 && x <= LED_WIDTH && y > 0 && y <= LED_HEIGHT) {
        matrix.setPixelColor(getPixelIndex(x, y), matrix.Color(0, 0, 0)); 
        matrix.show();
      }
    }
  }
}
