/*
  NeoEyes.h - Library for turning an 8x16 or two 8x8 NeoPixel matrix into a pair of expressive eyes
  Created by Sean Buchmeier +++, December 2023.
  License blah goes here
 */
#ifndef NeoEyes_h
#define NeoEyes_h

#include "Arduino.h"
#include "FastLED.h"

enum emote {
  neutral,
  right,
  left,
  up,
  down,
  happy,
  sad,
  angry,
  confused
};

class NeoEyes
{
  public:
    NeoEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    NeoEyes(int leftPin, int rightPin, ESPIChipsets chipSet, EOrder rgbOrder, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    void begin();
    void setExpression(emote expression);
    void setExpression(CRGB expression[][]);
  private:
    void setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
    uint16_t XY( uint8_t x, uint8_t y, bool _kMatrixSerpentineLayout = true, bool _kMatrixVertical = false);
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

    // This matrix has the pin position associated with each visual
    // array location point
    int pinPositions[8][16] = {
      // Row 1
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 2
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 3
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 4
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 5
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 6
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 7
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
      // Row 8
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
    };
};


#endif
