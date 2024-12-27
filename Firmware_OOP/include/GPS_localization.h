// GPS_localization.h
#ifndef GPS_LOCALIZATION_H
#define GPS_LOCALIZATION_H

#include <SparkFun_u-blox_GNSS_v3.h>
#include <Arduino.h>

// Global variables
extern float fltLongitude;
extern float fltLatitude;
extern String strLongitude;
extern String strLatitude;

// GPS Object
extern SFE_UBLOX_GNSS myGNSS;

// Function prototypes
void gpsInitialization();
void readGps();

#endif // GPS_LOCALIZATION_H
