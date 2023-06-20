#ifndef _SERVO_h
#define _SERVO_h

#include <stdint.h>

class Servo {

    private:
        uint8_t baseAngle;

    public:
        void servoWriteAngle(int postion);
};

extern Servo servo;
#endif