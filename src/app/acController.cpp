//#define DEBUG
#include "acController.h"
#include <IRsend.h>
#include <ir_Tcl.h>
#include "mqttConnect.h"
IRTcl112Ac myHomeAc(5);
extern PubSubClient mqttClient;

extern DallasTemperature sensors;
extern BH1750 lightMeter;
void acControllerInit()
{
  myHomeAc.begin();
}
void stationReport()
{
  StaticJsonDocument<100> doc;
  float lux = lightMeter.readLightLevel();
#ifdef DEBUG
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
#endif
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
#ifdef DEBUG
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(temp);
#endif
  doc["sensorPos"] = "Computer";
  doc["Lux"] = lux;
  doc["Temp"] = temp;
  char JSONmessageBuffer[100];
  // 将JSON消息打印到char缓冲区
  serializeJson(doc, JSONmessageBuffer);
  mqttClient.publish("nodeData", JSONmessageBuffer);
  mqttClient.loop();
  delay(5);
#ifdef DEBUG
  Serial.println(JSONmessageBuffer);
#endif
}
void acControl(String mqttContext)
{
  DynamicJsonDocument acControlDoc(100);
  deserializeJson(acControlDoc, mqttContext);
  if (acControlDoc["switch"] == "on")
  {
    myHomeAc.on();
    if (acControlDoc["mode"] == "cold")
    {
      myHomeAc.setMode(kTcl112AcCool);
      myHomeAc.setTemp(acControlDoc["temp"].as<float>());
    }
    else if(acControlDoc["mode"] == "dry")
    {
      myHomeAc.setMode(kTcl112AcDry);
    }
    else if(acControlDoc["mode"] == "heat")
    {
      myHomeAc.setMode(kTcl112AcHeat);
    }

    if (acControlDoc["fan"] == "high")
    {
      myHomeAc.setFan(kTcl112AcFanHigh);
    }
    else if(acControlDoc["fan"] == "mid")
    {
      myHomeAc.setFan(kTcl112AcFanMed);
    }
    else if(acControlDoc["fan"] == "min")
    {
      myHomeAc.setFan(kTcl112AcFanLow);
    }
    else if(acControlDoc["fan"] == "auto")
    {
      myHomeAc.setFan(kTcl112AcFanAuto);
    }
  }
  else if (acControlDoc["switch"] == "off")
  {
    myHomeAc.off();
  }

  myHomeAc.send();
}