
//#define DEBUG
#include <Arduino.h>
#include <string>
#include <ElegantOTA.h>
#include <esp_sleep.h>
extern void sersonInit();
extern void acControllerInit();
extern void taskInit();
extern void mqttInit();
extern void lcdInit();
WiFiClient espClient;
WebServer otaServer(80);
const char *ssid = "LightP";
const char *password = "980807PCH";
void setup()
{
  Serial.begin(115200);
  esp_sleep_enable_timer_wakeup(60000000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    #ifdef DEBUG
    Serial.println("Connecting to WiFi...");
    #endif
  }
  #ifdef DEBUG
  Serial.println("Connected to WiFi");
  #endif
  otaServer.on("/", []()
            { otaServer.send(200, "text/plain", "Hi! I am ESP8266."); });

  #ifdef DEBUG
  Serial.println(F("BH1750 Test"));

  Serial.println("Dallas Temperature IC Control Library Demo");
  #endif
  // 初始库
  ElegantOTA.begin(&otaServer); // Start ElegantOTA
  otaServer.begin();
  #ifdef DEBUG
  Serial.println(WiFi.localIP());
  #endif
  mqttInit();
  acControllerInit();
  sersonInit();
  lcdInit();
  taskInit();
}

void loop()
{}



