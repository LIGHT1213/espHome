#include "mqttConnect.h"
#include "acController.h"
#include <WiFi.h>
extern WiFiClient espClient;
PubSubClient mqttClient(espClient);
const char *mqtt_server = "192.168.31.220";
static void mqttCallback(char *topic, byte *payload, unsigned int length);

void mqttInit()
{
    mqttClient.setServer(mqtt_server, 1883);
    mqttClient.setCallback(mqttCallback);
    mqttClient.setKeepAlive(120);
}
static void mqttCallback(char *topic, byte *payload, unsigned int length)
{
  std::string cmpTopic(topic);
  const std::string acTopic = "acControllor";
  String mqttContext((char *)payload, length);
  if (cmpTopic == acTopic)
  {
    acControl(mqttContext);
  }
  else
  {
    #ifdef DEBUG
    Serial.print("topic not found");
    #endif
  }
}
void mqttReconnect()
{
  while (!mqttClient.connected())
  {
    #ifdef DEBUG
    Serial.print("Attempting MQTT connection...");
    #endif
    if (mqttClient.connect("ESP32Client"))
    {
      mqttClient.subscribe("acControllor");
      #ifdef DEBUG
      Serial.println("connected");
      #endif
    }
    else
    {
      #ifdef DEBUG
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      #endif
      delay(5000);
    }
  }
}