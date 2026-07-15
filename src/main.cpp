#include <Arduino.h>
#include <WiFi.h>

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);

    Serial.println();
    Serial.print("ESP32 STA MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop()
{
}