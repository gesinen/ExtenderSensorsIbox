/**
 * @file main.cpp
 * @author Daniel Burruchaga Sola  (danielburru@gmail.com)
 * @brief Extender sensors ibox project through arduino nano
 * @version 0.1
 * @date 2022-03-29
 *
 * @copyright Copyright Gesinen(c) 2022
 *
 * @TX_MODBUS 3
 * @RX_MODBUS 2
 *
 * @SensorDht0 4
 * @SensorDht1 5
 * @SensorDht2 6
 * @SensorDht3 7
 * @SensorDht4 8
 * @SensorDht5 9
 * @SensorDht6 10
 * @SensorDht7 11
 *
 */
#include <main.h>

/**
 * @brief initialize modbus serial port and enTxPin
 */
void initModbus()
{
  Serial.println("  Init Modbus...");
  pinMode(EnTxPin, OUTPUT);
  digitalWrite(EnTxPin, LOW); // RS485 como receptor
  modbus.begin(9600);
  modbus.setTimeout(100); // establecemos un tiempo de espera de 100ms
}

/**
 * @brief initialize all Sensors and pinSensors needed
 */
void initSensors()
{
  Serial.println("  Init Sensors...");
  // --- Out config ---
  pinMode(SensorDht0, OUTPUT);
  pinMode(SensorDht1, OUTPUT);
  pinMode(SensorDht2, OUTPUT);
  pinMode(SensorDht3, OUTPUT);
  pinMode(SensorDht4, OUTPUT);
  pinMode(SensorDht5, OUTPUT);
  pinMode(SensorDht6, OUTPUT);
  pinMode(SensorDht7, OUTPUT);

  digitalWrite(SensorDht0, LOW);
  digitalWrite(SensorDht1, LOW);
  digitalWrite(SensorDht2, LOW);
  digitalWrite(SensorDht3, LOW);
  digitalWrite(SensorDht4, LOW);
  digitalWrite(SensorDht5, LOW);
  digitalWrite(SensorDht6, LOW);
  digitalWrite(SensorDht7, LOW);

  Wire.begin();

  sht0.begin();
  sht1.begin();
  sht2.begin();
  sht3.begin();
  sht4.begin();
  sht5.begin();
  sht6.begin();
  sht7.begin();
}
/**
 * @brief Get the Sensors Data buffer from all sht
 * 
 * TODO: REVIEW FLOAT VALUES OF HUM AND TEMP
 */
void getSensorsData()
{
  // Sensor0
  uint8_t countBuff=0;
  for (uint8_t pinSensor = 4; pinSensor <= 11; pinSensor++)
  {
    digitalWrite(pinSensor, HIGH);
    
    Serial.print("Sensor ");
    Serial.print(pinSensor);
    Serial.print(" Temperature: ");
    // Read Temperature
    buffer[countBuff] = sht0.getTemperature(); 
    
    Serial.print(buffer[countBuff] );
    Serial.print(" Humidity: ");
    countBuff++;
    // Read Humidity
    buffer[countBuff] = sht0.getHumidity();   
    
    Serial.println(buffer[countBuff]);
    countBuff++;
    delay(5);
    digitalWrite(pinSensor, LOW);
    delay(10);
  }

  // Sensor0
}
/**
 * @brief readingModbus
 *
 *   La diferencia con los casos anteriores es en la trama para la comunicación, ahora es necesario enviar la dirección del esclavo, quedando la trama de la siguiente forma: \n
 *   [Inicio de trama][Dirección][Función][Valor][Fin de trama] \n
 *   La dirección es un número entero e indica con cual esclavo nos queremos comunicar. \n
 *   Ejemplos de esta trama serian: “I101S90F”,”I25S120F”,”I223LF”, etc. 
 *
 */
void readingModbus()
{
  //digitalWrite(EnTxPin, LOW); // RS485 como receptor por defecto
  if (modbus.find("i"))       // esperamos el inicio de trama
  {
    int esclavo = modbus.parseInt();            // recibimos la direccion del esclavo
    int dato = modbus.parseInt();               // recibimos el dato 00
    if (modbus.read() == 'f' && esclavo == 101) // si fin de trama y direccion son los correctos
    {
      // if we are the device who the master call 
      getSensorsData();
      sendDataModbus("I", "101", "L", "F"); // realizamos la acción con el dato recibido
    }
  }
 // digitalWrite(EnTxPin, HIGH); // RS485 como Transmisor
}
/**
 * @brief sendDataModbus
 *
 *   Ejemplos de esta trama serian: “I101S90F”,”I25S120F”,”I223LF”, etc:
 *
 * @param start  inicio de trama  "I"
 * @param address  direccion del esclavo    "101"
 * @param action  L para indicarle que vamos a Leer el sensor     "L"
 * @param end  fin de trama     "F"
 * 
 * TODO: REVIEW SEND BUFFER
 */

void sendDataModbus(String start, String address, String action, String end)
{
 digitalWrite(EnTxPin, HIGH); // RS485 como Transmisor

  modbus.print(start);   // inicio de trama  "I"
  modbus.print(address); // direccion del esclavo    "101"
  modbus.print(action);  // L para indicarle que vamos a Leer el sensor     "L"
  modbus.print(end);     // fin de trama     "F"
  modbus.flush();        // Esperamos hasta que se envíen los datos
  digitalWrite(EnTxPin, LOW); // RS485 como receptor DEFAULT

}


void setup()
{
  Serial.begin(9600);
  Serial.println("Starting extender sensor modbus...");
  initModbus();
  initSensors();
}

void loop()
{
  readingModbus();
}