#include <Arduino.h>
#include "myApp.h"
extern PubSubClient mqttClient;
extern WebServer otaServer;
extern TFT_eSPI tft;
void mqttTask(void *pvParameters);
void otaTask(void *pvParameters);
void lcdTask(void *pvParameters);

void taskInit()
{

    xTaskCreatePinnedToCore(
        mqttTask, "mqttTask" // 任务名
        ,
        4096 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 2 | portPRIVILEGE_BIT // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
        ,
        NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(
        otaTask, "otaTask" // 任务名
        ,
        1024 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 0 | portPRIVILEGE_BIT // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
        ,
        NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(
        lcdTask, "lcdTask" // 任务名
        ,
        4096 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 1 | portPRIVILEGE_BIT // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
        ,
        NULL, ARDUINO_RUNNING_CORE);
}
void mqttTask(void *pvParameters)
{

    while (true)
    {
        if (!mqttClient.connected())
        {
            mqttReconnect();
        }
        stationReport();
        vTaskDelay(1000);
    }
}
void otaTask(void *pvParameters)
{

    while (true)
    {
        otaServer.handleClient();
        vTaskDelay(50);
    }
}
void lcdTask(void *pvParameters)
{
    uint16_t x, y;
    while (true)
    {
        tft.getTouchRaw(&x, &y);
  
        Serial.printf("x: %i     ", x);

        Serial.printf("y: %i     ", y);

        Serial.printf("z: %i \n", tft.getTouchRawZ());
        vTaskDelay(30);
    }
}