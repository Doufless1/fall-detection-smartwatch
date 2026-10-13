#ifndef GYRO_SENSOR_H
#define GYRO_SENSOR_H

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <CircularBuffer.hpp>
#include "Config.h"

class GyroSensor {
public:
  GyroSensor();
  
  bool initialize();
  void calibrate();
  void process();
  void getAccelGyroData(float &accelMagnitude, float &gyroMagnitude);
  
  float getAccelX();
  float getAccelY();
  float getAccelZ();
  
  float getGyroX();
  float getGyroY();
  float getGyroZ();
  
  CircularBuffer<float, ACCEL_BUFFER_SIZE>& getAccelBuffer();
  CircularBuffer<float, GYRO_BUFFER_SIZE>& getGyroBuffer();
  
private:
  // Circular buffers keep a fixed window of recent samples: once full, each new sample
  // overwrites the oldest one, so RAM use stays constant. The getters above return
  // references to these buffers so they are never copied.
  Adafruit_MPU6050 mpu;
  CircularBuffer<float, ACCEL_BUFFER_SIZE> accelBuffer;
  CircularBuffer<float, GYRO_BUFFER_SIZE> gyroBuffer;
  
  float accelCalibX, accelCalibY, accelCalibZ;
  float gyroCalibX, gyroCalibY, gyroCalibZ;
  
  float lastAccelX, lastAccelY, lastAccelZ;
  float lastGyroX, lastGyroY, lastGyroZ;

float lastAccelMagnitude;
  float lastGyroMagnitude;
};

#endif // GYRO_SENSOR_H
