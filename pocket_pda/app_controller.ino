// Ported from https://github.com/abstractmachine/ArduboyController.

#include "logic.h"
#include <Keyboard.h>

#define A_BUTTON_KEY KEY_HOME
#define B_BUTTON_KEY KEY_END
#define LEFT_BUTTON_KEY KEY_LEFT_ARROW
#define RIGHT_BUTTON_KEY KEY_RIGHT_ARROW
#define UP_BUTTON_KEY KEY_UP_ARROW
#define DOWN_BUTTON_KEY KEY_DOWN_ARROW

#define TEXT_SIZE 1
#define CHAR_WIDTH (6 * TEXT_SIZE)
#define CHAR_HALF_WIDTH (CHAR_WIDTH / 2)
#define CHAR_HEIGHT (8 * TEXT_SIZE)
#define CHAR_HALF_HEIGHT (CHAR_HEIGHT / 2)
#define BUTTON_DIAMETER 18
#define BUTTON_RADIUS (BUTTON_DIAMETER / 2)
#define RECT_CORNER_SIZE 3

struct Button {
  uint8_t key;
  uint8_t button;
  char character;
  uint8_t x;
  uint8_t y;
};

static Button buttons[] = {
  { LEFT_BUTTON_KEY, LEFT_BUTTON,  '<', 14, 28 },
  { RIGHT_BUTTON_KEY, RIGHT_BUTTON, '>', 54, 28 },
  { UP_BUTTON_KEY, UP_BUTTON, '^', 34, 12 },
  { DOWN_BUTTON_KEY, DOWN_BUTTON, 'v', 34, 44 },
  { A_BUTTON_KEY, A_BUTTON, 'A', 94, 34 },
  { B_BUTTON_KEY, B_BUTTON, 'B', 114, 26 }
};

static void drawButton(PdaOS* os, int index, bool state) {
  uint8_t color = state ? BLACK : WHITE;
  uint8_t background = state ? WHITE : BLACK;
  uint8_t x = buttons[index].x;
  uint8_t y = buttons[index].y;
  if (buttons[index].button == A_BUTTON || buttons[index].button == B_BUTTON) {
    os->arduboy->fillCircle(x - 1, y - 1, BUTTON_RADIUS, background);
    os->arduboy->drawCircle(x - 1, y - 1, BUTTON_RADIUS, WHITE);
  } else {
    os->arduboy->fillRoundRect(x - BUTTON_RADIUS, y - BUTTON_RADIUS, BUTTON_DIAMETER, BUTTON_DIAMETER, RECT_CORNER_SIZE, background);
    os->arduboy->drawRoundRect(x - BUTTON_RADIUS, y - BUTTON_RADIUS, BUTTON_DIAMETER, BUTTON_DIAMETER, RECT_CORNER_SIZE, WHITE);
  }
  os->arduboy->drawChar(x - CHAR_HALF_WIDTH, y - CHAR_HALF_HEIGHT, buttons[index].character, color, background, TEXT_SIZE);
}

static void update(PdaOS* os, AppController* app) {
  uint8_t rls = 0;
  uint8_t pre = input(&rls);
  if (os->arduboy->pressed(LEFT_BUTTON + RIGHT_BUTTON + UP_BUTTON + DOWN_BUTTON + A_BUTTON + B_BUTTON)) {
    app->exit();
    os->app = -os->app;
    for (uint8_t i = 0; i < 6; ++i) {
      Keyboard.release(buttons[i].key);
    }
    return;
  }
  for (uint8_t i = 0; i < 6; ++i) {
    drawButton(os, i, os->arduboy->pressed(buttons[i].button));
    if ((pre & buttons[i].button) != 0)
      Keyboard.press(buttons[i].key);
    else if ((rls & buttons[i].button) != 0)
      Keyboard.release(buttons[i].key);
  }
  os->arduboy->setCursor(1, 56);
  os->arduboy->print("Hold all keys to exit");
}

void app_init_controller(PdaOS* os) {
  os->operation->init();
  Keyboard.begin();
}

void app_controller(PdaOS* os) {
  AppController* app = &os->ctrl;
  update(os, app);
}
