#define MPU6050_H

#include <Wire.h>
//Accelerometer and Gyroscope sensor Library
#include <MPU6050.h>

class MPU6050Manager {
public:
    MPU6050Manager();
    void initialize();
    void update();
    float getAccelX();
    float getAccelY();
    float getAccelZ();

private:
    MPU6050 mpu;
    unsigned long timer;
    float accelX, accelY, accelZ;
};

#endif // MPU6050_H