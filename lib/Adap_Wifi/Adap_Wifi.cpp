#include <WiFi.h>
#include "Config.h"
#include "Display.h"

void WifiInit()
{
    tft.printf("WiFi connecting");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        tft.printf(".");
    }
}
void WifiPrecess()
{
    //WiFi重连
}