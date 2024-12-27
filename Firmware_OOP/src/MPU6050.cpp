// mpu6050.cpp
#include "mpu6050.h"

MPU6050Manager::MPU6050Manager() : mpu(Wire), timer(0), accelX(0), accelY(0), accelZ(0) {}

void MPU6050Manager::initialize() {
    Wire.begin();
    byte status = mpu.begin();
    if (status != 0) {
        Serial.print("MPU6050 initialization failed with status: ");
        Serial.println(status);
        while (true);
    }

    Serial.println("MPU6050 initialized successfully");
    mpu.calcOffsets(true, true); // Automatically calculate offsets
}

void MPU6050Manager::update() {
    if (millis() - timer > 10) { // Update at 100Hz
        mpu.update();
        accelX = mpu.getAccX();
        accelY = mpu.getAccY();
        accelZ = mpu.getAccZ();
        timer = millis();
    }
}

float MPU6050Manager::getAccelX() {
    return accelX;
}

float MPU6050Manager::getAccelY() {
    return accelY;
}

float MPU6050Manager::getAccelZ() {
    return accelZ;
}
