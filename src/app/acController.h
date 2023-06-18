#ifndef __AC_CONTROLLER_H
#define __AC_CONTROLLER_H
#include <IRremoteESP8266.h>
#include "myJson.h"
#include <Wire.h>
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>
void acControl(String mqttContext);
void stationReport();
#endif