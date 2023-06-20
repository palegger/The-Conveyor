#ifndef _STEPMOTOR_h
#define _STEPMOTOR_h

#include <Arduino.h>

class StepMotor {

    public:
        void SendByte(byte addr, byte b);
        void SendCommand(byte addr, char *c);
        void goForward();
};

extern StepMotor stepMotor;
#endif