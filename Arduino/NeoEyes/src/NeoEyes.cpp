
// suppress FastLED pragma version message
// #define FASTLED_INTERNAL

// #include "Arduino.h"
// #include "FastLED.h"
#include "NeoEyes.h"

//NeoEyes::NeoEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder, int rightPin = -1, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
//NeoEyes::NeoEyes(int ledPin, int rightPin = -1, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
//void NeoEyes::setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false);
//uint16_t NeoEyes::XY( uint8_t x, uint8_t y, bool _kMatrixSerpentineLayout = true, bool _kMatrixVertical = false);

//NeoEyes::NeoEyes(int ledPin, int rightPin = -1, ESPIChipsets chipSet, EOrder rgbOrder, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
//NeoEyes::NeoEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder, int rightPin, bool kMatrixSerpentineLayout, bool kMatrixVertical) {
//NeoEyes::NeoEyes(uint8_t  ledPin, uint8_t  rightPin = -1, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
cNeoEyes::cNeoEyes(CRGB* ledPtr, uint16_t nLeds, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) 
  :
	_leds(ledPtr),
	maxLEDs(nLeds),
	numLEDs(nLeds)
{

    // _lPin = ledPin;
    // _isSeparate = false;
    // if (rightPin != -1)
    // {
    //   _rPin = rightPin;
    //   _isSeparate = true;
    // }
    //_chipSet = chipSet;
    //_rgbOrder = rgbOrder;
    setPinPositions(kMatrixSerpentineLayout, kMatrixVertical);
}

// NeoEyes::NeoEyes(int leftPin, int rightPin, ESPIChipsets chipSet, EOrder rgbOrder, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
//     _lPin = leftPin;
//     _rPin = rightPin;
//     _chipSet = chipSet;
//     _rgbOrder = rgbOrder;
//     _isSeparate = true;
//     setPinPositions(kMatrixSerpentineLayout, kMatrixVertical);
// }

//void NeoEyes::setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
void cNeoEyes::setPinPositions(bool kMatrixSerpentineLayout = true, bool kMatrixVertical = false) {
    for( uint8_t x = 0; x < _kMatrixWidth; x++) {
        for( uint8_t y = 0; y < _kMatrixHeight; y++) {
            // I have my rows set before my columns, so, y'know, height then width, w/e
            pinPositions[y][x] = XY(x,y,kMatrixSerpentineLayout,kMatrixVertical);
        }
    }
}

// void NeoEyes::begin(uint8_t  ledPin) {
//         //FastLED.addLeds<_chipSet, _lPin, _rgbOrder>(_leds,_nLeds);
//         FastLED.addLeds<NEOPIXEL, ledPin>(_leds,_NLEDS);
// }

// void NeoEyes::begin(uint8_t  leftPin, uint8_t  rightPin) {

//         // This will maybe work for chained matrices?
//         // FastLED.addLeds<_chipSet, _lPin, _rgbOrder>(_leds,0, _nLeds/2);
//         // FastLED.addLeds<_chipSet, _rPin, _rgbOrder>(_leds,_nLeds/2, _nLeds/2);
//         FastLED.addLeds<NEOPIXEL, leftPin>(_leds,0, _NLEDS/2);
//         FastLED.addLeds<NEOPIXEL, rightPin>(_leds,_NLEDS/2, _NLEDS/2);

//     //pinMode(_pin, OUTPUT);
// }
void cNeoEyes::begin(CLEDController& ctrl) {
  controller = &ctrl;
}

void cNeoEyes::setEmote(emote expression) {
    // set the matrix based on the chosen existing expression... or a custom matrix
    CRGB deadFace[8][16] = {{ CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red },
  // Row 2
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 3
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 4
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 5
  { CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black },
  // Row 6
  { CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black },
  // Row 7
  { CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Black },
  // Row 8
  { CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red, CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Red }
    };
    switch (expression) {
      case neutral:
      setExpression(deadFace);
      break;
      case right:
      setExpression(deadFace);
      break;
      case left:
      setExpression(deadFace);
      break;
      case up:
      setExpression(deadFace);
      break;
      case down:
      setExpression(deadFace);
      break;
      case happy:
      setExpression(deadFace);
      break;
      case sad:
      setExpression(deadFace);
      break;
      case angry:
      setExpression(deadFace);
      break;
      case confused:
      setExpression(deadFace);
      break;
      case dead:
      setExpression(deadFace);
      break;
      default:
        break;
    }
}

void cNeoEyes::setExpression(CRGB expression[8][16]) {
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
//uint16_t NeoEyes::XY( uint8_t x, uint8_t y, bool _kMatrixSerpentineLayout = true, bool _kMatrixVertical = false)
uint16_t cNeoEyes::XY( uint8_t x, uint8_t y, bool _kMatrixSerpentineLayout = true, bool _kMatrixVertical = false)
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

