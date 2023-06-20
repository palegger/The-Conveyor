#ifndef _RFID_h
#define _RFID_h

#include <MFRC522_I2C.h>

class Rfid {

    private:
        MFRC522 mfrc522();

    public:
        Rfid();
        boolean isCardPresent();
        unsigned long readCard();
};

#endif