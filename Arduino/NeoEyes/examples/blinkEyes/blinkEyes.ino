#include <NeoEyes.h>

#define DATA_PIN 12

NeoEyes<DATA_PIN> eyesss;

void setup() {
    eyesss.begin();
    eyesss.setNeutral();
}

void loop() {
    eyesss.blink(50);
    delay(500);
}