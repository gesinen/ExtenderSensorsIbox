# ExtenderSensorsIbox
 
ExtenderSensorsIbox trata de obtener sensores para el ibox a traves de un arduino nano y comunicacion modbus. Deben de tener cada uno que se conecte al mismo master (ibox) una dirección distinta.

```cpp
/*
 * PINES ARDUINO - MODULO MODBUS
 * @TX_MODBUS DI 3
 * @RX_MODBUS RO 2
 * @RE/DE 12
 *
 *PINES ARDUINO - SHT
 * @VCC 5v
 * @GND GND
 * @SDA SDA
 * @SCL SCL
*/

/**
 * @brief readingModbus
 *
 *   Quedando la trama de la siguiente forma: \n
 *   [Inicio de trama][Dirección][Función][Valor][Fin de trama] \n
 *   La dirección es un número entero e indica con cual esclavo nos queremos comunicar. \n
 *   Ejemplos de esta trama serian: 
 *     0x49 0x01 0x4c 0x46
  
  (al enviar esta peticion anterior devuelve...)
 *
 *     0x069  0x01 0x2c 0x00 0x00 0x00 0x00 0x66
 * Donde 0x00 en los bytes 4,5,6,7 obteneos los datos de temperatura 2bytes (Parte real en byte 1º y parte decimal en byte 2º) y humedad 2bytes (Parte real en byte 1º y parte decimal en byte 2º)
 */
```
