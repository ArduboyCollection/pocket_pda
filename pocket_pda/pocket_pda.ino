#include "data.h"
#include "logic.h"
#include "visual.h"
#include <Arduboy2.h>

static Operation P;
static Arduboy2 arduboy;

static void intro(void) {
  for (char i = -8; i < 28; i = i + 2) {
    arduboy.clear();
    arduboy.setCursor(34, i);
    arduboy.print("Pocket PDA");
    delay(20);
    arduboy.display();
  }
  delay(1000);
}

static uint8_t input(void) {
  if (!P.px && arduboy.pressed(RIGHT_BUTTON)) {
    P.px = true;
    return RIGHT_BUTTON;
  } else if (!P.px && arduboy.pressed(LEFT_BUTTON)) {
    P.px = true;
    return LEFT_BUTTON;
  } else if (!P.py && arduboy.pressed(UP_BUTTON)) {
    P.py = true;
    return UP_BUTTON;
  } else if (!P.py && arduboy.pressed(DOWN_BUTTON)) {
    P.py = true;
    return DOWN_BUTTON;
  } else if (P.px && arduboy.notPressed(RIGHT_BUTTON + LEFT_BUTTON)) {
    P.px = false;
  } else if (P.py && arduboy.notPressed(UP_BUTTON + DOWN_BUTTON)) {
    P.py = false;
  }
  if (!P.pa && arduboy.pressed(A_BUTTON)) {
    P.pa = true;
    return A_BUTTON;
  } else if (!P.pb && arduboy.pressed(B_BUTTON)) {
    P.pb = true;
    return B_BUTTON;
  } else if (P.pa && arduboy.notPressed(A_BUTTON)) {
    P.pa = false;
  } else if (P.pb && arduboy.notPressed(B_BUTTON)) {
    P.pb = false;
  }
  return 0;
}

static void draw(void) {
  arduboy.drawBitmap(0, 0, SPRITE_MENU0, 128, 64, WHITE);
}

void setup() {
  Serial.begin(9600);
  arduboy.begin();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(30);
  intro();
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();

  draw();

  Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  arduboy.display();
}
