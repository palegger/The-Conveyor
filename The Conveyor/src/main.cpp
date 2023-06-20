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
  mfrc522.PCD_Init();
  M5.Lcd.setTextSize(2);
  network.connection(const_cast<char *>(ssid), const_cast<char *>(password));
  stepMotor.goForward();
}

boolean isCardPresent() {
    if ( ! mfrc522.PICC_IsNewCardPresent())
            return false;
    if ( ! mfrc522.PICC_ReadCardSerial())
        return false;
    return true;
}

unsigned long readCard() {
    if (mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid))) {
        Serial.println("Tag authenticated");
        // lire les données de la page 4 du tag
        byte buffer[18];
        byte size = sizeof(buffer);
        if (mfrc522.MIFARE_Read(7, buffer, &size)) {
            Serial.println("Data read:");

            char hex[] = "";

            // afficher les données sur le port série en hexadécimal
            for (byte i = 0; i < size; i++)
            {
                Serial.print(buffer[i] < 0x10 ? "0" : "");
                Serial.print(buffer[i], HEX);
                Serial.print(" ");
            }

            unsigned long value = strtoul(hex, NULL, 16);

            Serial.println(value);

            // Halt PICC
            mfrc522.PICC_HaltA();
            // Stop encryption on PCD
            mfrc522.PCD_StopCrypto1();

            return value;
        }
    }
}

char * generateDataJson(int warehouse, int produit,String uid) {
  char* data1 = "";

  switch(warehouse) {
    case warehouse1: {
      data1 = "{\"product_id\": 1, \"warehouse_id\": 1,\"qty\": 1, \"movementcode\": \"";
    }
    break;
    case warehouse2: {
      data1 = "{\"product_id\": 2, \"warehouse_id\": 2,\"qty\": 1, \"movementcode\": \"";
    }
    break;
    case warehouse3: {
      data1 = "{\"product_id\": 3, \"warehouse_id\": 3,\"qty\": 1, \"movementcode\": \"";
    }
    break;
  }
  char* data1F = "\"}";
  char* newUid = (char*) uid.c_str();

  char *data = (char *) malloc(1 + strlen(data1) + strlen(newUid) + strlen(data1F));

  strcpy(data, data1);
  strcat(data, newUid);
  strcat(data, data1F);

  return data;
}

void loop() {
  unsigned long cardId;
  String uid = "";
  if(isCardPresent()) {
    for(int i = 0; i < 3; i++) {
      uid += String(mfrc522.uid.uidByte[i], HEX);
    }
    M5.lcd.println(uid);
    cardId = mfrc522.uid.uidByte[1];
  }

  int response;
  switch(cardId) {
    case 156: {
        char * data = generateDataJson(warehouse1, 1, uid);

        response = network.post(url, data, apikey);
        servo.servoWriteAngle(warehouse1);
        M5.Lcd.println("Post :");
        M5.Lcd.println(response);
        M5.Lcd.println("Warehouse 1");
      }
      break;
    case 151:{
        char * data = generateDataJson(warehouse2, 1, uid);

        response = network.post(url, data, apikey);
        servo.servoWriteAngle(warehouse2);
        M5.Lcd.println("Post :");
        M5.Lcd.println(response);
        M5.Lcd.println("Warehouse 1");
      }
      break;
    case 174: {
        char * data = generateDataJson(warehouse3, 1, uid);

        response = network.post(url, data, apikey);
        servo.servoWriteAngle(warehouse3);
        M5.Lcd.println("Post :");
        M5.Lcd.println(response);
        M5.Lcd.println("Warehouse 1");
      }
      break;
    default:
      M5.Lcd.println("No card");
      break;
   }
   delay(1000);
   M5.Lcd.clear();
   M5.Lcd.setCursor(0, 0);
}