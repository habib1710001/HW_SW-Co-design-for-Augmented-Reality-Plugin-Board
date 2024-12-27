// GPS_localization.c
#include "GPS_localization.h"

// Global variables
float fltLongitude = 0.0;
float fltLatitude = 0.0;
String strLongitude = "32";
String strLatitude = "45";

SFE_UBLOX_GNSS myGNSS;

void gpsInitialization() {
    myGNSS.enableDebugging(); // Enable debug messages on Serial

    while (myGNSS.begin() == false) {
        Serial.println(F("u-blox GNSS not detected at default I2C address. Retrying..."));
        delay(1000);
    }

    myGNSS.setI2COutput(COM_TYPE_UBX); // Set the I2C port to output UBX only (turn off NMEA noise)
}

void readGps() {
    if (myGNSS.getPVT() == true) {
        int32_t latitude = myGNSS.getLatitude();
        fltLatitude = static_cast<float>(latitude) / 10000000UL;
        strLatitude = String(fltLatitude);

        Serial.print(F("Lat: "));
        Serial.print(fltLatitude);
        Serial.print(" (degrees)");

        int32_t longitude = myGNSS.getLongitude();
        fltLongitude = static_cast<float>(longitude) / 10000000UL;
        strLongitude = String(fltLongitude);

        Serial.print(F(" Long: "));
        Serial.print(fltLongitude);
        Serial.print(" (degrees)");

        int32_t altitude = myGNSS.getAltitudeMSL(); // Altitude above Mean Sea Level
        Serial.print(F(" Alt: "));
        Serial.print(altitude);
        Serial.println(F(" (mm)"));
    } else {
        Serial.println(F("No updated position"));
    }
}
