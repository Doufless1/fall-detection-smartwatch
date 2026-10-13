#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Config.h"

// WiFi credentials and the API base URL live in secrets.h, which is not committed.
// Copy include/secrets.example.h to include/secrets.h and fill in your own values.
#if __has_include("secrets.h")
#include "secrets.h"
#else
#warning "include/secrets.h not found, using the placeholders from secrets.example.h"
#include "secrets.example.h"
#endif

// API endpoints
#define API_ENDPOINT API_BASE_URL "/SensorData"
#define REGISTER_ENDPOINT API_BASE_URL "/DeviceTokens/register"
#define GET_TOKEN_ENDPOINT API_BASE_URL "/get-test-token"
#define GET_DEVICE_CONFIG_ENDPOINT API_BASE_URL "/device-config/"
// Unique device identifier
#define DEVICE_ID "ESP32_FALL_001"

class NetworkManager {
public:
  NetworkManager();
  bool initialize(); // This will now also fetch the token and register
  bool sendSensorData(float accel, float gyro, bool fallDetected);
  void reconnect();
  bool fetchDeviceConfig();
  
private:
  bool isConnected;
  unsigned long lastDataSendTime;
  String authToken; 
  bool fetchAuthToken(); // New private method to get the token
  bool registerDeviceInternal(); // Renamed for clarity, called after token fetch
};

#endif // NETWORK_MANAGER_H
