/*
  LedEyes.h - Library for turning an 8x16 or two 8x8 NeoPixel matrix into a pair of expressive eyes
  Created by Sean Buchmeier +++, December 2023.
  License blah goes here
 */
#ifndef LedEyes_h
#define LedEyes_h

#include "Arduino.h"
#include "FastLED.h"
#include "LedEyes_emote.h"

class LedEyes
{
  public:
    LedEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder);
    LedEyes(int leftPin, int rightPin, ESPIChipsets chipSet, EOrder rgbOrder);
    void begin();
    void setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    void setExpression(emote expression);
    void setExpression(CRGB::HTMLColorCode expression[][]);
  private:
    int _lPin;
    int _rPin;
    bool _isSeparate = false;
    // 8x16, or 8x8 connected data out to data in of second 8x8
    const int _nLeds = 128;
    const int _kMatrixHeight = 8;
    const int _kMatrixWidth = 16;
    CRGB _leds[_nLeds];
    ESPIChipsets _chipSet;
    EOrder _rgbOrder;
};



#endif
