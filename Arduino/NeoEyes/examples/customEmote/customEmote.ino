#include <NeoEyes.h>

#define DATA_PIN 12

NeoEyes<DATA_PIN> eyesss;

CRGB defaultColors[4] = {CRGB::Black, CRGB::Blue, CRGB::MediumSpringGreen, CRGB::Red};

// neutral
Emote customEmote = { defaultColors,
  {     // Right Eye                   Left Eye
    { 3, 0, 1, 1, 1, 1, 0, 3,   3, 0, 1, 1, 1, 1, 0, 3 }, // Row 1
    { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 2
    { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 3
    { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 4
    { 1, 0, 0, 2, 2, 0, 0, 1,   1, 0, 0, 2, 2, 0, 0, 1 }, // Row 5
    { 1, 0, 0, 0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 0, 0, 1 }, // Row 6
    { 0, 1, 0, 0, 0, 0, 1, 0,   0, 1, 0, 0, 0, 0, 1, 0 }, // Row 7
    { 3, 0, 1, 1, 1, 1, 0, 3,   3, 0, 1, 1, 1, 1, 0, 3 }, // Row 8
  } };

void setup() {
    eyesss.begin();
}

void loop() {
    eyesss.setExpression(customEmote);
    delay(500);
}