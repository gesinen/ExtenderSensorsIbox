#include <Arduino.h>
#include <SoftwareSerial.h>
#include "tinySHT2x.h"
#include <Wire.h>
//---Modbus config---
// Modbus enable tx pin
#define EnTxPin 1
// Modbus tx pin
#define TX_MODBUS 3
// Modbus rx pin
#define RX_MODBUS 2
//--- End Modbus config---

//--- Sensors config ---
#define SensorDht0 4
#define SensorDht1 5
#define SensorDht2 6
#define SensorDht3 7
#define SensorDht4 8
#define SensorDht5 9
#define SensorDht6 10
#define SensorDht7 11
//--- End Sensors config ---

SoftwareSerial modbus(2, 3); // RX, TX

tinySHT2x sht0;
tinySHT2x sht1;
tinySHT2x sht2;
tinySHT2x sht3;
tinySHT2x sht4;
tinySHT2x sht5;
tinySHT2x sht6;
tinySHT2x sht7;

// Data Buffer with the sensorsdata as  SensorDht0Temp, SensorDht0Hum, SensorDht1Temp, SensorDht1Hum ...
uint8_t buffer[16];

void sendDataModbus(String start, String address, String action, String end);
void initSensors();
void getSensorsData();
void readingModbus();
void initModbus();