#include "shellPort.h"
#include <Arduino.h>
#include <WiFi.h>

Shell shell;
WiFiClass WiFi;
char shellBuffer[512];

/**
 * @brief 用户shell写
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return unsigned short 写入实际长度
 */
signed short userShellWrite(char *data, unsigned short len)
{
    return Serial.write((const char *)data, len);
}


/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return unsigned short 读取实际长度
 */
signed short userShellRead(char *data, unsigned short len)
{
    return Serial.read((uint8_t *)data, len);
}
void userShellInit(void)
{
    shell.write = userShellWrite;
    shell.read = userShellRead;
    shellInit(&shell, shellBuffer, 512);

    
}
void printfMyIp()
{
    Serial.println(WiFi.localIP());
}
