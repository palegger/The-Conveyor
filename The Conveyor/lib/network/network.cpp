#include "network.h"
#include <M5Stack.h>
#include <WiFi.h>
#include <HttpClient.h>

void Network::connection(char* ssid, char* password) 
{
    WiFi.begin(ssid, password);
    M5.Lcd.print("Connecting to WiFi ");
    while(WiFi.status() != WL_CONNECTED){
        M5.Lcd.print(".");
        delay(100);
    }
    M5.Lcd.clearDisplay();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("Connected to the WiFi ");
    M5.Lcd.println(ssid);
    M5.Lcd.print("IP address: ");
    M5.Lcd.println(WiFi.localIP());
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