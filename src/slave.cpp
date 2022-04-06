#include <main.h>
uint8_t mydireccion = 0x01;   // Direccion del esclavo
uint8_t initPayloadMb = 0x49; // Inicio trama
uint8_t dataPayloadMb = 0x4c; // Inicio trama
uint8_t endPayloadMb = 0x46;  // End trama
SoftwareSerial modbus(2, 3);  // R0, DE

/**
 * @brief initialize all Sensors and pinSensors needed
 */
void initSensors()
{
  Serial.println("  Init Sensors...");
  // --- Out config ---
  Wire.begin();
  sht.begin();
}

/**
 * @brief initialize modbus serial port and enTxPin
 */
void initModbus()
{
  Serial.println("  Init Modbus...");
  pinMode(EnTxPin, OUTPUT);
  digitalWrite(EnTxPin, LOW); // RS485 como receptor
  modbus.begin(9600);
  modbus.setTimeout(1000); // establecemos un tiempo de espera de 100ms
}
/**
 * @brief Get the Sensors Data buffer from all sht
 *
 * TODO: REVIEW FLOAT VALUES OF HUM AND TEMP
 */
void getSensorsData()
{
  // Read Temperature
  float temp = sht.getTemperature();
  float hum = sht.getHumidity();

  // Temp without decimal point
  uint8_t noDecTemp = temp;
  buffer[0] = noDecTemp;
  buffer[1] = (noDecTemp - temp) * 100;

  Serial.print(" Temperature: ");
  Serial.print(buffer[0]);
  Serial.print(".");
  Serial.println(buffer[1]);

  // Read Humidity
  // Hum without decimal point
  uint8_t noDecHum = hum;
  buffer[2] = noDecHum;
  buffer[3] = (noDecHum - hum) * 100;

  Serial.print(" Humidity: ");
  Serial.print(buffer[2]);
  Serial.print(".");
  Serial.println(buffer[3]);
}
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(100); // establecemos un tiempo de espera de 100ms
  initModbus();
  initSensors();
}

void loop()
{
  if (modbus.available())
  {
    Serial.println(" TX available"); // inicio de trama

    if (modbus.read() == initPayloadMb) // Si recibimos el inicio de trama
    {
      uint8_t direccion = modbus.read(); // recibimos la direccion
      if (direccion == mydireccion)      // Si direccion es la nuestra
      {
        char funcion = modbus.read(); // leemos el carácter de función

        //---Si el carácter de función  es L entonces el maestro está solicitando una lectura del sensor---
        if (funcion == dataPayloadMb)
        {
          if (modbus.read() == endPayloadMb) // Si el fin de trama es el correcto
          {
            getSensorsData();
            digitalWrite(EnTxPin, HIGH); // rs485 como transmisor
            modbus.print("i");           // inicio de trama
            modbus.write(mydireccion);   // direccion
            modbus.print(",");
            modbus.write(buffer[0]);      // valor del sensor
            modbus.write(buffer[1]);      // valor del sensor
            modbus.write(buffer[2]);      // valor del sensor
            modbus.write(buffer[3]);      // valor del sensor
            modbus.print("f");          // fin de trama
            modbus.flush();             // Esperamos hasta que se envíen los datos
            digitalWrite(EnTxPin, LOW); // RS485 como receptor
            Serial.println(" TX DONE"); // inicio de trama
          }
        }
      }
    }
  }
  delay(10);
}