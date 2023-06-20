#include <stepMotor.h>
#include <M5Stack.h>
#include <Wire.h>

#define STEPMOTOR_I2C_ADDR 0x70

void StepMotor::SendByte(byte addr, byte b) {
    Wire.beginTransmission(addr);
    Wire.write(b);
    Wire.endTransmission();
}

void StepMotor::SendCommand(byte addr, char *c) {
    Wire.beginTransmission(addr);
    while ((*c) != 0) {
        Wire.write(*c);
        c++;
    }
    Wire.write(0x0d);
    Wire.write(0x0a);
    Wire.endTransmission();
}

void StepMotor::goForward() {
        Serial.println("Go forward");
        SendCommand(STEPMOTOR_I2C_ADDR, "G1 X10000Y10000Z10000 F180");

}

StepMotor stepMotor;