#include "servo.h"
#include <M5Stack.h>
#include <Arduino.h>
#include <Wire.h>

#define GOPLUS_ADDR 0x38
enum Warehouse { warehouse1, warehouse2, warehouse3 };

void Servo::servoWriteAngle(int position) {
    Wire.beginTransmission(GOPLUS_ADDR);
    Wire.write( (uint8_t)0);
    switch(position) {
        case warehouse1:
            Serial.println("warehouse1");
            Wire.write((uint8_t)17);
            break;
        case warehouse2:
            Serial.println("warehouse2");
            Wire.write((uint8_t)33);
            break;
        case warehouse3:
            Serial.println("warehouse3");
            Wire.write((uint8_t)55);
            break;
    }
    Wire.endTransmission();
}

Servo servo;