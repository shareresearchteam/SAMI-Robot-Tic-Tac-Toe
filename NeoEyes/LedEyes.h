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
    void begin();
    void setExpression(emote expression);
    void setExpression(CRGB::HTMLColorCode expression[][]);
  private:
    int _pin;
    // 8x16, or 8x8 connected data out to data in of second 8x8
    int _nLeds = 128;
    CRGB _leds[_nLeds];
    ESPIChipsets _chipSet;
    EOrder _rgbOrder;
};



#endif
