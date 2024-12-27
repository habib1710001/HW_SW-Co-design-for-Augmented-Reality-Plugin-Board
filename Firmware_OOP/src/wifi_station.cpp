// wifi_station.cpp
#include "wifi_station.h"

WiFiManager::WiFiManager() : ssid("esp"), password("123456789"), server(80), gpsStatus(0), navStatus(0), verStatus(0), saveStatus(0) {}

void WiFiManager::initializeWiFi() {
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    } else {
        Serial.println("Mounting successful with SPIFFS");
    }

    // Set up Access Point
    Serial.println("Setting AP (Access Point)");
    WiFi.softAP("TITAN-WIFI-MANAGER", NULL);
    IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
}

void WiFiManager::initializeServer() {
    setupRoutes();
    server.begin();
    Serial.println("HTTP server started");
}

String WiFiManager::handleProcessor(const String& var) {
    if (var == "satNo") {
        satNo = "32";
        return satNo;
    } else if (var == "Lat") {
        Latitude = "45.0"; // Placeholder, replace with actual GPS data
        return Latitude;
    } else if (var == "Long") {
        Longitude = "32.0"; // Placeholder, replace with actual GPS data
        return Longitude;
    } else if (var == "gpsStatus") {
        return gpsStatus ? "OFF" : "ON";
    } else if (var == "navStatus") {
        return navStatus ? "OFF" : "ON";
    } else if (var == "verStatus") {
        return verStatus ? "OFF" : "ON";
    } else if (var == "saveStatus") {
        return saveStatus ? "RESET" : "SAVE";
    }
    return String();
}

void WiFiManager::setupRoutes() {
    // Root page
    server.on("/", HTTP_GET, [&](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/diagnostic.html", String(), false, [&](const String& var) { return handleProcessor(var); });
    });

    // Diagnostic page
    server.on("/diagnostic.html", HTTP_GET, [&](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/diagnostic.html", String(), false, [&](const String& var) { return handleProcessor(var); });
    });

    // GPS toggle
    server.on("/gpsToggle", HTTP_GET, [&](AsyncWebServerRequest *request) {
        gpsStatus = !gpsStatus;
        request->send(SPIFFS, "/index.html", String(), false, [&](const String& var) { return handleProcessor(var); });
    });

    // Navigation toggle
    server.on("/navToggle", HTTP_GET, [&](AsyncWebServerRequest *request) {
        navStatus = !navStatus;
        request->send(SPIFFS, "/index.html", String(), false, [&](const String& var) { return handleProcessor(var); });
    });

    // Vertical toggle
    server.on("/verToggle", HTTP_GET, [&](AsyncWebServerRequest *request) {
        verStatus = !verStatus;
        request->send(SPIFFS, "/index.html", String(), false, [&](const String& var) { return handleProcessor(var); });
    });

    // Save configuration
    server.on("/save", HTTP_GET, [&](AsyncWebServerRequest *request) {
        saveStatus = !saveStatus;
        request->send(SPIFFS, "/index.html", String(), false, [&](const String& var) { return handleProcessor(var); });
    });

    // Static resources
    server.on("/style.css", HTTP_GET, [&](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/style.css", "text/css");
    });
}
