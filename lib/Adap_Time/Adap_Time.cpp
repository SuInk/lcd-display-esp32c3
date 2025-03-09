
#include <NTPClient.h>
#include <HTTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 8 * 3600, 60000);
const String day[] = {"日", "一", "二", "三", "四", "五", "六"};
void TimeInit()
{
    timeClient.begin();
    timeClient.update();
}

void UpdataTime(void* param)
{
    while(1)
    {
        timeClient.update();
        vTaskDelay(200 / portTICK_PERIOD_MS);

    }
}
String GetShowDate()
{
    unsigned long timestamp = timeClient.getEpochTime(); // 时间戳
    struct tm *ptm = localtime((time_t *)&timestamp);
    String month = (ptm->tm_mon + 1 < 10) ? "0" + String(ptm->tm_mon + 1) : String(ptm->tm_mon + 1);
    String day = (ptm->tm_mday < 10) ? "0" + String(ptm->tm_mday) : String(ptm->tm_mday);
    return String(1900 + ptm->tm_year) + "/" + month + "/" + day;
}
String GetShowDay()
{
    return "星期" + day[timeClient.getDay()];
}
String GetShowTime()
{
    return timeClient.getFormattedTime();
}