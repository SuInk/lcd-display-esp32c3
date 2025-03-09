
#include <Arduino.h>

#include "Display.h"
#include "Adap_Time.h"
#include "Adap_Wifi.h"
#include "Adap_Gpio.h"

// ===================================================
TaskHandle_t pvCreatedTask1 = NULL;
TaskHandle_t pvCreatedTask2 = NULL;
TaskHandle_t pvCreatedTask3 = NULL;
void setup()
{
    Serial.begin(115200); // 串口初始化
    GpioInit();           // 管脚和ADC初始化
    LcdInit();            // tft-lcd初始化
    WifiInit();           // wifi初始化
    TimeInit();           // ntp初始化
    xTaskCreatePinnedToCore(UpdataTime, "UpdataTime", 1024, NULL, 2, &pvCreatedTask1, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(GpioCtrl, "GpioCtrl", 1024 * 3, NULL, 1, &pvCreatedTask2, ARDUINO_RUNNING_CORE);
    xTaskCreatePinnedToCore(LcdDisplay, "LcdDisplay", 1024 * 2, NULL, 1, &pvCreatedTask3, ARDUINO_RUNNING_CORE);
}
void loop()
{
    // 任务栈高水位线检测
    Serial.printf("%d|%d|%d\n", uxTaskGetStackHighWaterMark(pvCreatedTask1), uxTaskGetStackHighWaterMark(pvCreatedTask2), uxTaskGetStackHighWaterMark(pvCreatedTask3));
    delay(1000);
}
