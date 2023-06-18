#include "mySensor.h"
#define ONE_WIRE_BUS 4 // 定义DS18B20数据口连接ESP32的4号IO上
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BH1750 lightMeter;
void sersonInit()
{
  Wire.begin();
  lightMeter.begin();
  sensors.begin();
}