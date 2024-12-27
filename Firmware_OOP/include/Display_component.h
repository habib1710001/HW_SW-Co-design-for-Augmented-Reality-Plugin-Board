// Display_component.h
#ifndef DISPLAY_COMPONENT_H
#define DISPLAY_COMPONENT_H

#include <U8g2lib.h>
#include <Wire.h>

class DisplayManager {
public:
    DisplayManager();
    void initialize();
    void drawDefaultPage(float accelX, float accelY, float accelZ);
    void drawMenuPage(int subPage);
    void drawSettingsPage(int subSubPage);
    void drawDiagnosticsPage(int subSubPage);
    void drawAboutPage();
    void drawReticlePage(int option);
    void drawGpsDisplayPage(int option);
    void drawNavigationDisplayPage(int option);
    void drawVerticalLevelPage(int option);

private:
    U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI display;
    void constrainPosition(int& xPos, int& yPos, int width, int height);
};

#endif // DISPLAY_COMPONENT_H