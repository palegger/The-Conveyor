#include <rfid.h>
#include <Arduino.h>
    
MFRC522::MIFARE_Key key;
MFRC522 mfrc522(0x28);

Rfid::Rfid() {
    mfrc522.PCD_Init();
}

boolean Rfid::isCardPresent() {
    if ( ! mfrc522.PICC_IsNewCardPresent())
            return false;
    if ( ! mfrc522.PICC_ReadCardSerial())
        return false;
    return true;
}

unsigned long Rfid::readCard() {
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