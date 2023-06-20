#include <Arduino.h>
#include <M5Stack.h>
#include <Wire.h>
#include "network.h"
#include "servo.h"
#include "stepMotor.h"
// #include "rfid.h"
#include <MFRC522_I2C.h>
#include <memory.h>
#include <stdlib.h>

using namespace std;

const char* ssid = "";
const char* password = "";
char* url = "http://172.20.10.4:80/dolibarr/api/index.php/stockmovements";

char* apikey = "";

enum Warehouse { warehouse1, warehouse2, warehouse3 };

// Rfid rfid;
MFRC522 mfrc522(0x28);
MFRC522::MIFARE_Key key;

void setup() {
  M5.begin(true, false);
  M5.Power.begin();
  Wire.begin();
  M5.Lcd.setTextSize(4);
  M5.Lcd.println("  Test Mode");
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("");
  network.connection(const_cast<char *>(ssid), const_cast<char *>(password));
  M5.Lcd.print("Wifi module ");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("OK");
  M5.Lcd.setTextColor(WHITE);
  mfrc522.PCD_Init();
  M5.Lcd.print("RFID module ");
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("OK");
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.print("Stepmotor module ");
  M5.Lcd.setTextColor(ORANGE);
  M5.Lcd.println("MOUVING");
  M5.Lcd.setTextColor(WHITE);
  stepMotor.goForward();
  M5.Lcd.print("Servo module ");
  M5.Lcd.setTextColor(ORANGE);
  M5.Lcd.println("MOUVING");
  M5.Lcd.setTextColor(WHITE);
  servo.servoWriteAngle(warehouse1);
  servo.servoWriteAngle(warehouse3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.println("");
  M5.Lcd.println("Check the stepmotor and servo is really moving");
  M5.Lcd.println("");
  M5.Lcd.setTextSize(4);
  M5.Lcd.println("    Ready");
}

void loop() {
  servo.servoWriteAngle(warehouse1);
  delay(3000);
  servo.servoWriteAngle(warehouse3);
  delay(3000);
}