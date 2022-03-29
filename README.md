# ExtenderSensorsIbox
 
ExtenderSensorsIbox trata de obtener un extensor de sensores para el ibox a traves de un arduino nano. Los pines detallados a continucación muestran 
a que pìnes se conectan el VCC de cada sensor obteniendo así la posibilidad de encender cada sensor a traves de cada uno de ellos 
para poder encender preguntar y capturar hum/temp de cada sensor, estos valores se almacenan en un buffer y se envia a traves de modbus.

"""
/*
 * PINES MODBUS
 * @TX_MODBUS 3
 * @RX_MODBUS 2
 * PINES VCC DE CADA SENSOR
 * @SensorDht0 4
 * @SensorDht1 5
 * @SensorDht2 6
 * @SensorDht3 7
 * @SensorDht4 8
 * @SensorDht5 9
 * @SensorDht6 10
 * @SensorDht7 11
*/
/**
 * @brief readingModbus
 *
 *   La diferencia con los casos anteriores es en la trama para la comunicación, ahora es necesario enviar la dirección del esclavo, quedando la trama de la siguiente forma: \n
 *   [Inicio de trama][Dirección][Función][Valor][Fin de trama] \n
 *   La dirección es un número entero e indica con cual esclavo nos queremos comunicar. \n
 *   Ejemplos de esta trama serian: “I101S90F”,”I25S120F”,”I223LF”, etc. 
 *
 */
"""