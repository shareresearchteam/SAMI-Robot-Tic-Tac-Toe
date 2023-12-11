
#include "Arduino.h"
#include "FastLED.h"
#include "NeoEyes.h"

NeoEyes::NeoEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
    _lPin = ledPin;
    _chipSet = chipSet;
    _rgbOrder = rgbOrder;
    _isSeparate = false;
    setPinPositions(kMatrixSerpentineLayout, kMatrixVertical);
}

NeoEyes::NeoEyes(int leftPin, int rightPin, ESPIChipsets chipSet, EOrder rgbOrder, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
    _lPin = leftPin;
    _rPin = rightPin;
    _chipSet = chipSet;
    _rgbOrder = rgbOrder;
    _isSeparate = true;
    setPinPositions(kMatrixSerpentineLayout, kMatrixVertical);
}

void NeoEyes::setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
    for( uint8_t x = 0; x < _kMatrixWidth; x++) {
        for( uint8_t y = 0; y < _kMatrixHeight; y++) {
            // I have my rows set before my columns, so, y'know, height then width, w/e
            pinPositions[y][x] = XY(x,y,kMatrixSerpentineLayout,kMatrixVertical);
        }
    }
}

void NeoEyes::begin() {
    if (_isSeparate){
        // This will maybe work for chained matrices?
        FastLED.addLeds<_chipSet, _lPin, _rgbOrder>(_leds,0, _nLeds/2);
        FastLED.addLeds<_chipSet, _rPin, _rgbOrder>(_leds,_nLeds/2, _nLeds/2);
    }
    else{
        FastLED.addLeds<_chipSet, _lPin, _rgbOrder>(_leds,_nLeds);
    }
    //pinMode(_pin, OUTPUT);
}

void NeoEyes::setExpression(emote expression) {
    // set the matrix based on the chosen existing expression... or a custom matrix
    switch (expression) {
      case neutral:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case right:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case left:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case up:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case down:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case happy:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case sad:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case angry:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      case confused:
      setExpression({
  // Row 1
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 2
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 4
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 5
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 6
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 8
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black }
});
      break;
      default:
      break;
    }
}

void NeoEyes::setExpression(CRGB expression[][]) {
    // set the matrix based on the chosen existing expression... or a custom matrix
    for (int i = 0; i < _kMatrixHeight; i ++) {
        for (int j = 0; j < _kMatrixWidth; j++) {
            // so, this is for a static index...
            _leds[pinPositions[i][j]] = expression[i][j];
        }
    }
    FastLED.show();
}

// Convert the x,y position to led index flexibly
uint16_t NeoEyes::XY( uint8_t x, uint8_t y, bool _kMatrixSerpentineLayout = true, bool _kMatrixVertical = false)
{
  uint16_t i;
  
  if( _kMatrixSerpentineLayout == false) {
    if (_kMatrixVertical == false) {
      i = (y * _kMatrixWidth) + x;
    } else {
      i = _kMatrixHeight * (_kMatrixWidth - (x+1))+y;
    }
  }

  if( _kMatrixSerpentineLayout == true) {
    if (_kMatrixVertical == false) {
      if( y & 0x01) {
        // Odd rows run backwards
        uint8_t reverseX = (_kMatrixWidth - 1) - x;
        i = (y * _kMatrixWidth) + reverseX;
      } else {
        // Even rows run forwards
        i = (y * _kMatrixWidth) + x;
      }
    } else { // vertical positioning
      if ( x & 0x01) {
        i = _kMatrixHeight * (_kMatrixWidth - (x+1))+y;
      } else {
        i = _kMatrixHeight * (_kMatrixWidth - x) - (y+1);
      }
    }
  }
  
  return i;
}

