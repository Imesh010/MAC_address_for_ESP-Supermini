#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

uint8_t masterMAC[] = {0x30, 0x76, 0xF5, 0xE7, 0xE6, 0x24};

typedef struct
{
    int nodeID;
    int counter;
} SensorData;

SensorData data;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("Send Status : ");

    if (status == ESP_NOW_SEND_SUCCESS)
        Serial.println("Success");
    else
        Serial.println("Failed");
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    Serial.println("ESP32-C3 Sender");
    Serial.print("My MAC : ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_register_send_cb(OnDataSent);

    esp_now_peer_info_t peerInfo = {};

    memcpy(peerInfo.peer_addr, masterMAC, 6);
    peerInfo.channel = 1;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to Add Peer");
        return;
    }

    data.nodeID = 1;
    data.counter = 0;

    Serial.println("Sender Ready");
}

void loop()
{
    data.counter++;

    esp_err_t result = esp_now_send(
        masterMAC,
        (uint8_t *)&data,
        sizeof(data));

    Serial.print("Counter : ");
    Serial.println(data.counter);

    Serial.print("Send Result : ");
    Serial.println(result);

    delay(2000);
}