
#include "NeoEyes.h"



cNeoEyes::cNeoEyes(CRGB* ledPtr, uint16_t nLeds, bool kMatrixSerpentineLayout = true, bool kMatrixVertical = true) 
  :
	_leds(ledPtr)
{
    //setPinPositions(kMatrixSerpentineLayout, kMatrixVertical);
    _kMatrixSerpentineLayout = kMatrixSerpentineLayout;
    _kMatrixVertical = kMatrixVertical;
}

void cNeoEyes::begin(CLEDController& ctrl) {
  controller = &ctrl;
}

void cNeoEyes::setExpression(Emote expression) {
  currentEmote = expression;
  for (int i = 0; i < _kMatrixHeight; i ++) {
    for (int j = 0; j < _kMatrixWidth; j++) {
      // so, this is for a static index...
      _leds[XY(j,i)] = expression.colorList[expression.pattern[i][j]];
    }
  }
  FastLED.show();
}

void cNeoEyes::setExpression(CRGB expression[8][16]) {
    // set the matrix based on the chosen existing expression... or a custom matrix
    for (int i = 0; i < _kMatrixHeight; i ++) {
        for (int j = 0; j < _kMatrixWidth; j++) {
            // so, this is for a static index...
            _leds[XY(j,i)] = expression[i][j];
        }
    }
    FastLED.show();
}

void cNeoEyes::setNeutral() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
      { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
      { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
      { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 4
      { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 5
      { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
      { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
      { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::setRight(bool isSlight = true) {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  if(isSlight) {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
        { 1, 0, 2, 2, 0, 0, 0, 1,   1, 0, 2, 2, 0, 0, 0, 1 }, // Row 4
        { 1, 0, 2, 2, 0, 0, 0, 1,   1, 0, 2, 2, 0, 0, 0, 1 }, // Row 5
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
  else {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
        { 1, 2, 2, 0, 0, 0, 0, 1,   1, 2, 2, 0, 0, 0, 0, 1 }, // Row 4
        { 1, 2, 2, 0, 0, 0, 0, 1,   1, 2, 2, 0, 0, 0, 0, 1 }, // Row 5
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
}

void cNeoEyes::setLeft(bool isSlight = true) {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  if(isSlight) {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
        { 1, 0, 0, 0, 2, 2, 0, 1,   1, 0, 0, 0, 2, 2, 0, 1 }, // Row 4
        { 1, 0, 0, 0, 2, 2, 0, 1,   1, 0, 0, 0, 2, 2, 0, 1 }, // Row 5
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
  else {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
        { 1, 0, 0, 0, 0, 2, 2, 1,   1, 0, 0, 0, 0, 2, 0, 1 }, // Row 4
        { 1, 0, 0, 0, 0, 2, 2, 1,   1, 0, 0, 0, 0, 2, 0, 1 }, // Row 5
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
}

void cNeoEyes::setUp(bool isSlight = true) {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  if(isSlight) {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 3
        { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 4
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 5
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
  else {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 2, 2, 0, 1, 0,   0, 1, 0, 2, 2, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 3
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 4
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 5
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
}

void cNeoEyes::setDown(bool isSlight = true) {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  if(isSlight) {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 4
        { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 5
        { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
  else {
    currentEmote = { defaultColors,
      {     // Right Eye                   Left Eye
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 1
        { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 4
        { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 5
        { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 6
        { 0, 1, 0, 2, 2, 0, 1, 0,   0, 1, 0, 2, 2, 0, 1, 0 }, // Row 7
        { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 1, 1, 1, 0, 0 }, // Row 8
      } };
    setExpression(currentEmote);
  }
}

void cNeoEyes::setHappy() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 1
      { 0, 0, 0, 1, 1, 0, 0, 0,   0, 0, 0, 1, 1, 0, 0, 0 }, // Row 2
      { 0, 0, 1, 0, 0, 1, 0, 0,   0, 0, 1, 0, 0, 1, 0, 0 }, // Row 3
      { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 4
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 5
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 6
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 7
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::setSad() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 1
      { 0, 0, 0, 0, 1, 1, 1, 0,   0, 1, 1, 1, 0, 0, 0, 0 }, // Row 2
      { 0, 0, 0, 1, 0, 0, 0, 1,   1, 0, 0, 0, 1, 0, 0, 0 }, // Row 3
      { 0, 0, 1, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 1, 0, 0 }, // Row 4
      { 0, 1, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 1, 0 }, // Row 5
      { 1, 0, 0, 0, 2, 2, 0, 1,   1, 0, 2, 2, 0, 0, 0, 1 }, // Row 6
      { 1, 0, 0, 0, 2, 2, 0, 1,   1, 0, 2, 2, 0, 0, 0, 1 }, // Row 7
      { 0, 1, 1, 1, 1, 1, 1, 0,   0, 1, 1, 1, 1, 1, 1, 0 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::setAngry() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 1
      { 0, 1, 1, 1, 0, 0, 0, 0,   0, 0, 0, 0, 1, 1, 1, 0 }, // Row 2
      { 1, 0, 0, 0, 1, 0, 0, 0,   0, 0, 0, 1, 0, 0, 0, 1 }, // Row 3
      { 1, 0, 0, 0, 0, 1, 0, 0,   0, 0, 1, 0, 0, 0, 0, 1 }, // Row 4
      { 1, 0, 0, 2, 2, 0, 1, 0,   0, 1, 0, 2, 2, 0, 0, 1 }, // Row 5
      { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 6
      { 0, 1, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 1, 0 }, // Row 7
      { 0, 0, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 0, 0 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::setConfused(bool isSplit = true) {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  if(isSplit) {
    currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 0, 0, 0 }, // Row 1
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 1, 0, 1, 0, 0 }, // Row 2
      { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 1, 0, 0, 0, 1, 0 }, // Row 3
      { 0, 1, 0, 0, 0, 0, 1, 0,   0, 0, 1, 0, 2, 0, 1, 0 }, // Row 4
      { 1, 0, 0, 2, 2, 0, 0, 1,   0, 0, 1, 0, 2, 0, 1, 0 }, // Row 5
      { 0, 1, 0, 0, 0, 0, 1, 0,   0, 0, 1, 0, 0, 0, 1, 0 }, // Row 6
      { 0, 0, 1, 1, 1, 1, 0, 0,   0, 0, 0, 1, 0, 1, 0, 0 }, // Row 7
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 0, 0, 0 }, // Row 8
    } };
    setExpression(currentEmote);
  }
  else {
    Emote currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 0, 0 }, // Row 1
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 1, 0, 1, 0 }, // Row 2
      { 0, 0, 1, 1, 1, 1, 1, 1,   0, 0, 0, 1, 0, 0, 0, 1 }, // Row 3
      { 0, 1, 0, 0, 0, 0, 0, 0,   1, 0, 0, 1, 0, 2, 0, 1 }, // Row 4
      { 1, 0, 0, 0, 2, 2, 0, 0,   0, 1, 0, 1, 0, 2, 0, 1 }, // Row 5
      { 0, 1, 0, 0, 0, 0, 0, 0,   1, 0, 0, 1, 0, 0, 0, 1 }, // Row 6
      { 0, 0, 1, 1, 1, 1, 1, 1,   0, 0, 0, 0, 1, 0, 1, 0 }, // Row 7
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 0, 0 }, // Row 8
    } };
    setExpression(currentEmote);
  }
}

void cNeoEyes::setClosed() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 1
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 2
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 3
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 4
      { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 5
      { 0, 0, 1, 0, 0, 1, 0, 0,   0, 0, 1, 0, 0, 1, 0, 0 }, // Row 6
      { 0, 0, 0, 1, 1, 0, 0, 0,   0, 0, 0, 1, 1, 0, 0, 0 }, // Row 7
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::setSleepy() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 1
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 2
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 3
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 4
      { 0, 1, 1, 1, 1, 1, 1, 0,   0, 1, 1, 1, 1, 1, 1, 0 }, // Row 5
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 6
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 7
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::setDead() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 3, 0, 0, 0, 0, 0, 0, 3,   3, 0, 0, 0, 0, 0, 0, 3 }, // Row 1
      { 0, 3, 0, 0, 0, 0, 3, 0,   0, 3, 0, 0, 0, 0, 3, 0 }, // Row 2
      { 0, 0, 3, 0, 0, 3, 0, 0,   0, 0, 3, 0, 0, 3, 0, 0 }, // Row 3
      { 0, 0, 0, 3, 3, 0, 0, 0,   0, 0, 0, 3, 3, 0, 0, 0 }, // Row 4
      { 0, 0, 0, 3, 3, 0, 0, 0,   0, 0, 0, 3, 3, 0, 0, 0 }, // Row 5
      { 0, 0, 3, 0, 0, 3, 0, 0,   0, 0, 3, 0, 0, 3, 0, 0 }, // Row 6
      { 0, 3, 0, 0, 0, 0, 3, 0,   0, 3, 0, 0, 0, 0, 3, 0 }, // Row 7
      { 3, 0, 0, 0, 0, 0, 0, 3,   3, 0, 0, 0, 0, 0, 0, 3 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::setOff() {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  currentEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 1
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 2
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 3
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 4
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 5
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 6
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 7
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 8
    } };
  setExpression(currentEmote);
}

void cNeoEyes::blink(int closeTime = 50) {
  CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};
  Emote closedEmote = { defaultColors,
    {     // Right Eye                   Left Eye
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 1
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 2
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 3
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 4
      { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 5
      { 0, 0, 1, 0, 0, 1, 0, 0,   0, 0, 1, 0, 0, 1, 0, 0 }, // Row 6
      { 0, 0, 0, 1, 1, 0, 0, 0,   0, 0, 0, 1, 1, 0, 0, 0 }, // Row 7
      { 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 }, // Row 8
    } };
  setExpression(closedEmote);
  FastLED.show();
  delay(closeTime);
  setExpression(currentEmote);
  FastLED.show();
}

void cNeoEyes::setBrightness(uint8_t scale) {
  FastLED.show(scale);
}

// Convert the x,y position to led index flexibly
uint16_t cNeoEyes::XY( uint8_t x, uint8_t y)
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

