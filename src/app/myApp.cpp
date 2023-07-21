#include <Arduino.h>
#include "myApp.h"
#include "../src/shell/shell_cpp.h"
#include "FreeRTOSConfig.h"
extern PubSubClient mqttClient;
extern WebServer otaServer;
extern TFT_eSPI tft;
extern Shell shell;
void mqttTask(void *pvParameters);
void otaTask(void *pvParameters);
void lcdTask(void *pvParameters);
void weatherTimeTask(void *pvParameters);
//void shellTask(void *pvParameters);


QueueHandle_t xBinarySemaphore = xSemaphoreCreateBinary();
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
        4096 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 2 | portPRIVILEGE_BIT // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
        ,
        NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(
        lcdTask, "lcdTask" // 任务名
        ,
        9000 // This stack size can be checked & adjusted by reading the Stack Highwater
        ,
        NULL, 2 | portPRIVILEGE_BIT // 任务优先级, with 3 (configMAX_PRIORITIES - 1) 是最高的，0是最低的.
        ,
        NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(
        shellTask, "shell"
        , 
        4096
        , 
        &shell, 2 | portPRIVILEGE_BIT
        , 
        NULL, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(
        weatherTimeTask, "weatherTimeTask"
        , 
        4096
        , 
        NULL, 2 | portPRIVILEGE_BIT
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
void weatherTimeTask(void *pvParameters)
{
    while (true)
    {
        
        vTaskDelay(1000);
    }
}
void lcdTask(void *pvParameters)
{
    while (true)
    {
        
        vTaskDelay(30);
    }
}

