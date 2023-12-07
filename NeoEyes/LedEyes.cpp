
#include "Arduino.h"
#include "FastLED.h"
#include "LedEyes.h"

LedEyes::LedEyes(int ledPin, ESPIChipsets chipSet, EOrder rgbOrder) {
    _pin = ledPin;
    _chipSet = chipSet;
    _rgbOrder = rgbOrder;
}

void LedEyes::begin() {
    FastLED.addLeds<_chipSet, _pin, _rgbOrder>(_leds,_nLeds);
    //pinMode(_pin, OUTPUT);
}

void LedEyes::setExpression(emote expression) {
    // set the matrix based on the chosen existing expression... or a custom matrix
}

void LedEyed::setExpression(CRGB::HTMLColorCode expression[][]) {

}

