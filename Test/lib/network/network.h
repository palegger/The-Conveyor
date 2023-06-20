#include <string>
using namespace std;

#ifndef _NETWORK_h
#define _NETWORK_h

class Network {

    private:
        char* ssid;
        char* password;

    public:
        void connection(char* ssid, char* password);
        int post(char* url, char* data, char* apikey);
        int get(char* url);
};

extern Network network;
#endif