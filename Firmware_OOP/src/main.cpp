// Augmented Reality Glass Plugin Board Main Code
#include <Arduino.h>
#include "mpu6050.h"
#include "GPS_localization.h"
#include "wifi_station.h"
#include "Display_component.h"

/************************************* Configurations **********************************************/
#define PIN_USER_SWITCH 15
#define PIN_USER_LED 16
#define TIME_LONG_PRESS 500
#define TIME_SHORT_PRESS 100

/************************************* Classes and Objects **********************************************/

class ButtonHandler {
public:
    ButtonHandler(uint8_t pin) : pin(pin), presses(0), releases(0), pressed(true), released(false), lastInterruptTime(0) {
        pinMode(pin, INPUT_PULLUP);
        attachInterrupt(pin, ButtonHandler::isr, CHANGE);
        instance = this;
    }

    static void IRAM_ATTR isr() {
        unsigned long currentTime = millis();
        if ((currentTime - instance->lastInterruptTime) > TIME_SHORT_PRESS) {
            if (instance->pressed) {
                instance->presses++;
                instance->pressTime = currentTime;
                instance->pressed = false;
                instance->released = true;
                Serial.println("Button Pressed: " + String(instance->pressTime));
            } else {
                instance->releases++;
                instance->releaseTime = currentTime;
                instance->pressed = true;
                instance->released = false;
                Serial.println("Button Released: " + String(instance->releaseTime));

                instance->handlePressDuration(instance->releaseTime - instance->pressTime);
            }
            instance->lastInterruptTime = currentTime;
        }
    }

    void handlePressDuration(unsigned long duration) {
        if (duration >= TIME_LONG_PRESS) {
            layerNo++;
            Serial.println("Long Press Detected, Layer: " + String(layerNo));
        } else {
            manageLayerNavigation();
        }
    }

    void manageLayerNavigation() {
        if (layerNo == 2) {
            subPageNo = (subPageNo + 1) % 4;
            Serial.println("Subpage: " + String(subPageNo));
        } else if (layerNo == 3) {
            subSubPageNo = (subSubPageNo + 1) % (endLimit3 + 1);
            Serial.println("Sub-Subpage: " + String(subSubPageNo));
        } else if (layerNo == 4) {
            endOptionNo = (endOptionNo + 1 > endLimit4) ? 1 : endOptionNo + 1;
            Serial.println("End Option: " + String(endOptionNo));
        } else if (layerNo > 5) {
            layerNo = 5;
        }
    }

private:
    uint8_t pin;
    unsigned long pressTime, releaseTime, lastInterruptTime;
    uint32_t presses, releases;
    bool pressed, released;
    static ButtonHandler* instance;
};

ButtonHandler* ButtonHandler::instance = nullptr;

class DisplayManager {
public:
    void initialize() {
        displayInitilization();
    }

    void renderPage(int layer, int page, int subPage, int subSubPage) {
        u8g2.clearBuffer();
        switch (layer) {
            case 1:
                drawPageDefault();
                break;
            case 2:
                drawPageManue();
                break;
            case 3:
                renderSubPage(subPage);
                break;
            case 4:
                renderSubSubPage(subPage, subSubPage);
                break;
            default:
                drawPageDefault();
                break;
        }
        u8g2.sendBuffer();
    }

private:
    void renderSubPage(int subPage) {
        switch (subPage) {
            case 0: layerNo = 1; pageNo = 0; break;
            case 1: drawPageSettings(); break;
            case 2: drawPageDiagnostics(); break;
            case 3: drawPageAbout(); break;
        }
    }

    void renderSubSubPage(int subPage, int subSubPage) {
        if (subPage == 1) {
            switch (subSubPage) {
                case 1: drawPageReticle(); break;
                case 2: drawPageGpsDisplay(); break;
                case 3: drawPageNevigationDisplay(); break;
                case 4: drawPageVerticleLevel(); break;
            }
        }
    }
};

class DeviceManager {
public:
    void initializeDevices() {
        mpuInitilization();
        wifiInitialization();
        gpsInitialization();
        handlePageConfig();
    }
};

/************************************* Main Application **********************************************/
int main() {
    Serial.begin(115200);
    pinMode(PIN_USER_LED, OUTPUT);

    ButtonHandler button1(PIN_USER_SWITCH);
    DisplayManager displayManager;
    DeviceManager deviceManager;

    deviceManager.initializeDevices();
    displayManager.initialize();

    while (1) {
        displayManager.renderPage(layerNo, pageNo, subPageNo, subSubPageNo);
        delay(10); // Control refresh rate
    }

    return 0;
}
