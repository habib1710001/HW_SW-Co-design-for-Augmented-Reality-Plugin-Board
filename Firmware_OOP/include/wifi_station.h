// wifi_station.h
#ifndef WIFI_STATION_H
#define WIFI_STATION_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>

class WiFiManager {
public:
    WiFiManager();
    void initializeWiFi();
    void initializeServer();

private:
    const char* ssid;
    const char* password;
    AsyncWebServer server;
    IPAddress IP;

    // Device status variables
    int gpsStatus;
    int navStatus;
    int verStatus;
    int saveStatus;

    String satNo;
    String Longitude;
    String Latitude;

    String handleProcessor(const String& var);
    void setupRoutes();
};

#endif // WIFI_STATION_H