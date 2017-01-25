#include "logic.h"

typedef void (* ButtonClickedEventHandler)(PdaOS*, AppCalculator*);

static void onButtonNumClicked(PdaOS* os, AppCalculator* app, int8_t n) {
}

static void onButton0Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton1Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton2Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton3Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton4Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton5Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton6Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton7Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton8Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButton9Clicked(PdaOS* os, AppCalculator* app) {
}

static void onButtonDotClicked(PdaOS* os, AppCalculator* app) {
}

static void onButtonAddClicked(PdaOS* os, AppCalculator* app) {
}

static void onButtonMinClicked(PdaOS* os, AppCalculator* app) {
}

static void onButtonMulClicked(PdaOS* os, AppCalculator* app) {
}

static void onButtonDivClicked(PdaOS* os, AppCalculator* app) {
}

static void onButtonEvalClicked(PdaOS* os, AppCalculator* app) {
}

static void input(PdaOS* os, AppCalculator* app) {
  const ButtonClickedEventHandler handlers[] = {
    onButton7Clicked, onButton8Clicked, onButton9Clicked, onButtonDivClicked,
    onButton4Clicked, onButton5Clicked, onButton6Clicked, onButtonMulClicked,
    onButton1Clicked, onButton2Clicked, onButton3Clicked, onButtonMinClicked,
    onButton0Clicked, onButtonDotClicked, onButtonEvalClicked, onButtonAddClicked
  };
  switch (input()) {
    case LEFT_BUTTON:
      if (--app->cursor.x < 0) app->cursor.x = 3;
      break;
    case RIGHT_BUTTON:
      if (++app->cursor.x > 3) app->cursor.x = 0;
      break;
    case UP_BUTTON:
      if (--app->cursor.y < 0) app->cursor.y = 3;
      break;
    case DOWN_BUTTON:
      if (++app->cursor.y > 3) app->cursor.y = 0;
      break;
    case A_BUTTON:
      handlers[app->cursor.x + app->cursor.y * 4](os, app);
      break;
    case B_BUTTON:
      os->app = -os->app;
      break;
  }
}

static void draw(PdaOS* os, AppCalculator* app) {
  os->arduboy->drawRect(5, 5, 118, 13, WHITE);
  os->arduboy->setCursor(8, 8);
  os->arduboy->print("0123456789012345678");
  const char CHARS[] = { '7', '8', '9', '/', '4', '5', '6', '*', '1', '2', '3', '-', '0', '.', '=', '+' };
  const uint8_t x = 21, y = 20;
  const uint8_t w = 20, h = 9;
  const uint8_t ix = 2, iy = 2;
  for (uint8_t j = 0; j < 4; ++j) {
    for (uint8_t i = 0; i < 4; ++i) {
      os->arduboy->setCursor(x + i * (w + ix) + 7, y + j * (h + iy) + 1);
      os->arduboy->write(CHARS[i + j * 4]);
      os->arduboy->drawRect(x + i * (w + ix), y + j * (h + iy), w, h, WHITE);
    }
  }
  os->arduboy->drawRect(x + app->cursor.x * (w + ix) - 1, y + app->cursor.y * (h + iy) - 1, w + 2, h + 2, WHITE);
}

void app_calculator(PdaOS* os) {
  AppCalculator* app = &os->calc;
  input(os, app);
  draw(os, app);
}
