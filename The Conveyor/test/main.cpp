#include <Arduino.h>
#include <M5Stack.h>

void setup() {
  M5.begin(true, false);
  M5.Power.begin();
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.Lcd.println("Hello World!");
  delay(1000);
}