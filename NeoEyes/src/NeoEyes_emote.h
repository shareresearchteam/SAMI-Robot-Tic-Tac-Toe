#ifndef NeoEyes_emote_h
#define NeoEyes_emote_h

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

// CRGBPalette16 defaultColors = { 
//   CRGB::Black, CRGB::Red,    CRGB::Yellow, CRGB::Green, 
//   CRGB::Blue,  CRGB::Purple, CRGB::White, 0x000117, 
//   0x000019, 0x00001C, 0x000026, 0x000031, 
//   0x00003B, 0x000046, 0x14554B, 0x28AA50 
// };

// Which pallete index to use for each matrix position
// alternatively just use the CRGB enum set instead lol
CRGB Neutral[8][16] = {
  { // Row 1
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  },
  { // Row 2
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  },
  { // Row 3
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  },
  { // Row 4
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  },
  { // Row 5
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  },
  { // Row 6
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  },
  { // Row 7
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  },
  { // Row 8
    CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::, CRGB::
  }
};

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



#endif