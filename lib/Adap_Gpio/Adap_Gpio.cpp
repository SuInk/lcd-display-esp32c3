#include <Arduino.h>
#include "Config.h"

#define BL_CTRL 11
#define GM 4
#define D12 12 // 主板led灯
#define D13 13


typedef enum : uint8_t
{
    InputHigh = 0,
    InputLow,
    PreSwitch,

} eInputState;
eInputState InputState = InputHigh;

void GpioInit()
{
    pinMode(BL_CTRL, OUTPUT); // 背光控制
#if USE_GM_DO
    pinMode(GM, INPUT); // 连接光控传感器DO口
    digitalWrite(BL_CTRL, HIGH);
#else
    analogSetPinAttenuation(GM, ADC_11db);
    pinMode(GM, ANALOG); // 连接光控传感器AO口
    analogWrite(BL_CTRL, 150);
#endif
}
void BackLightCtrl()
{
#if USE_GM_DO
    switch (InputState)
    {
    case InputHigh:
        if (digitalRead(GM) == HIGH)
        {
            InputState = InputHigh;
            digitalWrite(BL_CTRL, LOW);
        }
        else
        {
            InputState = PreSwitch;
        }
        break;
    case InputLow:
        if (digitalRead(GM) == LOW)
        {
            InputState = InputLow;
            digitalWrite(BL_CTRL, HIGH);
        }
        else
        {
            InputState = PreSwitch;
        }
        break;
    case PreSwitch:
        if (digitalRead(GM) == LOW)
        {
            InputState = InputLow;
        }
        else
        {
            InputState = InputHigh;
        }
        break;
    default:
        break;
    }
#else
    float vin = analogReadMilliVolts(GM) / 1000.0;
    float scale = pow((1 - vin / 2.853), 0.5);
    scale<0?scale=0:scale;
    uint8_t value =  scale * 255;
    Serial.printf("%f|%d\n", vin, value);
    analogWrite(BL_CTRL, value);
#endif
}
void GpioCtrl(void *param)
{
    while(1)
    {
        BackLightCtrl();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}