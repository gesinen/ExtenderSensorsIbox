#include <Arduino.h>
#include <SoftwareSerial.h>
#include "tinySHT2x.h"
#include <Wire.h>
//---Modbus config---
// Modbus enable tx pin
#define EnTxPin 12
// Modbus tx pin
#define TX_MODBUS 3
// Modbus rx pin
#define RX_MODBUS 2
//--- End Modbus config---


tinySHT2x sht;

// Data Buffer with the sensorsdata as  SensorDht0Temp, SensorDht0Hum, SensorDht1Temp, SensorDht1Hum ...
uint8_t buffer[16];

void sendDataModbus(String start, String address, String action, String end);
void initSensors();
void getSensorsData();
void readingModbus();
void initModbus();