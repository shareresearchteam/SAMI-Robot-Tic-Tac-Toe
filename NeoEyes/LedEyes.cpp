
#include "Arduino.h"
#include "FastLED.h"
#include "LedEyes.h"

LedEyes::LedEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder) {
    _lPin = ledPin;
    _chipSet = chipSet;
    _rgbOrder = rgbOrder;
    _isSeparate = false;
    setPinPositions();
}

LedEyes::LedEyes(int leftPin, int rightPin, ESPIChipsets chipSet, EOrder rgbOrder) {
    _lPin = leftPin;
    _rPin = rightPin;
    _chipSet = chipSet;
    _rgbOrder = rgbOrder;
    _isSeparate = true;
    setPinPositions();
}

void LedEyes::setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
    for( uint8_t x = 0; x < _kMatrixWidth; x++) {
        for( uint8_t y = 0; y < _kMatrixHeight; y++) {
            // I have my rows set before my columns, so, y'know, height then width, w/e
            pinPositions[y][x] = XY(x,y);
        }
    }
}

void LedEyes::begin() {
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

void LedEyes::setExpression(emote expression) {
    // set the matrix based on the chosen existing expression... or a custom matrix
    for (int i = 0; i < _kMatrixHeight; i ++) {
        for (int j = 0; j < _kMatrixWidth; j++) {
            // so, this is for a static index...
            _leds[pinPositions[i][j]] = Neutral[i][j];
        }
    }
    FastLED.show();
}

void LedEyed::setExpression(CRGB::HTMLColorCode expression[][]) {

}

// Convert the x,y position to led index flexibly
uint16_t XY( uint8_t x, uint8_t y)
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

