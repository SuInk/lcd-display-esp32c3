#pragma once
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void LcdInit();
void LcdDisplay(void* param);