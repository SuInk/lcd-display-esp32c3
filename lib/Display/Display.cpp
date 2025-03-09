#include "Display.h"
#include "Config.h"

#include "NotoSansBold36.h"
#include "Consolaz.h"
#include "YaHei.h"
#include "Font.h"
#include "BgImage.h"
#include "Adap_Time.h"

// 全局变量
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
void LcdInit()
{
    tft.init();
    tft.setRotation(0);
    tft.setTextColor(TEXT_COLOR);
    tft.setTextSize(2);
    tft.fillScreen(BG_COLOR);
}
void LcdDisplay(void *param)
{
    spr.createSprite(TFT_WIDTH, TFT_HEIGHT);
    spr.setTextColor(TEXT_COLOR, TEXT_COLOR, false);
    while (1)
    {
        spr.pushImage(0, 0, TFT_WIDTH, TFT_HEIGHT, bg_image);
        spr.loadFont(NotoSansSC_ExtraBold24);
        spr.setCursor(10, 5, 2);
        spr.println(GetShowDate());
        spr.setTextDatum(TR_DATUM);
        spr.drawString(GetShowDay(),TFT_WIDTH-10,5);
        spr.unloadFont();
        spr.loadFont(Consolaz);
        spr.setCursor(10, 5 + TFT_HEIGHT * 0.1, 2);
        spr.println(GetShowTime());
        spr.unloadFont();
        spr.pushSprite(0, 0);
        delay(200);
    }
}