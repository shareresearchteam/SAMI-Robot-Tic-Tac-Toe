#include <NeoEyes.h>

#define DATA_PIN 12

NeoEyes<DATA_PIN> eyesss;

void setup() {
    eyesss.begin();
}

void loop() {
    eyesss.setEmote(neutral);
    delay(500);
    eyesss.setEmote(happy);
    delay(500);
}