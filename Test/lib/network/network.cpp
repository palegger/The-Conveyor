#include "network.h"
#include <M5Stack.h>
#include <WiFi.h>
#include <HttpClient.h>

void Network::connection(char* ssid, char* password) 
{
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
        delay(100);
    }
}

int Network::post(char* url, char* data, char* apikey) 
{
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("DOLAPIKEY", apikey);
    int httpResponseCode = http.POST(data);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    return httpResponseCode;
}

int Network::get(char* url) 
{
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    return httpResponseCode;
}
Network network;