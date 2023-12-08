#include <NeoEyes.h>

NeoEyes eyesss(12, NeoPixel,  GRB);

void setup() {
    eyesss.begin();
}

void loop() {
    eyesss.setExpression(neutral);
    delay(500);
    eyesss.setExpression(happy);
    delay(500);
}