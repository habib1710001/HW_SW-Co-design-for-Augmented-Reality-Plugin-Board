// Display_component.cpp
#include "Display_component.h"

DisplayManager::DisplayManager()
    : display(U8G2_R0, /* cs=*/5, /* dc=*/33, /* reset=*/25) {}

void DisplayManager::initialize() {
    display.begin();
    display.clearBuffer();
    display.setFontMode(1);
    display.setBitmapMode(1);
    Serial.println("Display initialized.");
}

void DisplayManager::constrainPosition(int& xPos, int& yPos, int width, int height) {
    xPos = constrain(xPos, 0, display.getDisplayWidth() - width);
    yPos = constrain(yPos, 0, display.getDisplayHeight() - height);
}

void DisplayManager::drawDefaultPage(float accelX, float accelY, float accelZ) {
    static int xPos = 0;
    static int yPos = 0;

    xPos += map(accelX * 1000, -32768, 32767, -15, 15);
    yPos += map(accelY * 1000, -32768, 32767, -15, 15);
    constrainPosition(xPos, yPos, 33, 33);

    display.clearBuffer();
    display.drawXBMP(xPos, yPos, 33, 33, image_bits);

    int centerX = (display.getDisplayWidth() - 35) / 2;
    int centerY = (display.getDisplayHeight() - 35) / 2;
    display.drawXBMP(centerX, centerY, 35, 35, image_triangle_bits);

    display.setFont(u8g2_font_5x7_tr);
    display.drawStr(0, 62, "Default Page");
    display.sendBuffer();
}

void DisplayManager::drawMenuPage(int subPage) {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "Menu Page");
    display.drawFrame(1, subPage * 10, 126, 11);
    display.sendBuffer();
}

void DisplayManager::drawSettingsPage(int subSubPage) {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "Settings Page");
    display.drawFrame(1, subSubPage * 10, 126, 11);
    display.sendBuffer();
}

void DisplayManager::drawDiagnosticsPage(int subSubPage) {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "Diagnostics Page");
    display.drawFrame(1, subSubPage * 10, 126, 11);
    display.sendBuffer();
}

void DisplayManager::drawAboutPage() {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "About Page");
    display.sendBuffer();
}

void DisplayManager::drawReticlePage(int option) {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "Reticle Page");
    display.drawFrame(1, option * 10, 126, 11);
    display.sendBuffer();
}

void DisplayManager::drawGpsDisplayPage(int option) {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "GPS Display Page");
    display.drawFrame(1, option * 10, 126, 11);
    display.sendBuffer();
}

void DisplayManager::drawNavigationDisplayPage(int option) {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "Navigation Display Page");
    display.drawFrame(1, option * 10, 126, 11);
    display.sendBuffer();
}

void DisplayManager::drawVerticalLevelPage(int option) {
    display.clearBuffer();
    display.setFont(u8g2_font_5x8_tr);
    display.drawStr(10, 10, "Vertical Level Page");
    display.drawFrame(1, option * 10, 126, 11);
    display.sendBuffer();
}
