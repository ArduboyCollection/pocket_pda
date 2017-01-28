#include "data.h"
#include "logic.h"
#include "visual.h"
#include <Arduboy2.h>

static PdaOS OS;
static Arduboy2 A;

static void intro(void) {
  for (char i = -8; i < 28; i = i + 2) {
    A.clear();
    A.setCursor(34, i);
    A.print("Pocket PDA");
    A.setCursor(46, i + 8);
    A.print("V0.8.0");
    delay(20);
    A.display();
  }
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  A.begin();
  A.initRandomSeed();
  A.setFrameRate(FPS);
  intro();
  OS.arduboy = &A;
  initLogic(&OS);
}

void loop() {
  if (!(A.nextFrame()))
    return;
  A.clear();
  run(&OS);
  A.display();
}
