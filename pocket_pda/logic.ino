#include "logic.h"

static Operation P;

static uint8_t input(void) {
  uint8_t result = 0;
  if (!P.pr && A.pressed(RIGHT_BUTTON)) {
    P.pr = true;
    result += RIGHT_BUTTON;
  } else if (P.pr && A.notPressed(RIGHT_BUTTON)) {
    P.pr = false;
  }
  if (!P.pl && A.pressed(LEFT_BUTTON)) {
    P.pl = true;
    result += LEFT_BUTTON;
  } else if (P.pl && A.notPressed(LEFT_BUTTON)) {
    P.pl = false;
  }
  if (!P.pu && A.pressed(UP_BUTTON)) {
    P.pu = true;
    result += UP_BUTTON;
  } else if (P.pu && A.notPressed(UP_BUTTON)) {
    P.pu = false;
  }
  if (!P.pd && A.pressed(DOWN_BUTTON)) {
    P.pd = true;
    result += DOWN_BUTTON;
  } else if (P.pd && A.notPressed(DOWN_BUTTON)) {
    P.pd = false;
  }
  if (!P.pa && A.pressed(A_BUTTON)) {
    P.pa = true;
    result += A_BUTTON;
  } else if (P.pa && A.notPressed(A_BUTTON)) {
    P.pa = false;
  }
  if (!P.pb && A.pressed(B_BUTTON)) {
    P.pb = true;
    result += B_BUTTON;
  } else if (P.pb && A.notPressed(B_BUTTON)) {
    P.pb = false;
  }
  return result;
}

static void menu(PdaOS* os) {
  int8_t &app = os->app;
  switch (input()) {
    case LEFT_BUTTON:
      ++app;
      if (app == 0) app = -(APP_END - 1);
      break;
    case RIGHT_BUTTON:
      --app;
      if (app == -APP_END) app = -APP_BEGIN;
      break;
    case UP_BUTTON:
      app += 3;
      if (app >= 0) app = -(APP_END - 1);
      break;
    case DOWN_BUTTON:
      app -= 3;
      if (app <= -APP_END) app = -APP_BEGIN;
      break;
    case A_BUTTON:
      app = -app;
      break;
  }
  if (app <= -APP_BEGIN && app > -(APP_BEGIN + 6)) os->arduboy->drawBitmap(0, 0, SPRITE_MENU0, 128, 64, WHITE);
  else os->arduboy->drawBitmap(0, 0, SPRITE_MENU1, 128, 64, WHITE);
  int8_t idx = -app;
  uint8_t x = (idx - 1) % 3;
  uint8_t y = ((idx - 1) / 3) % 2;
  os->arduboy->drawRect(x * 40 + 8, y * 32, 32, 32, WHITE);
}

static void calculator(PdaOS* os) {
  switch (input()) {
    case B_BUTTON:
      os->app = -os->app;
      break;
  }
  os->arduboy->setCursor(0, 0);
  os->arduboy->print("1234567890");
}

static void flashlight(PdaOS* os) {
}

static void finances(PdaOS* os) {
}

static void chronograph(PdaOS* os) {
}

static void countdown(PdaOS* os) {
}

static void calendar(PdaOS* os) {
}

static void games(PdaOS* os) {
}

static void controller(PdaOS* os) {
}

static void todo(PdaOS* os) {
}

void run(PdaOS* os) {
  switch (os->app) {
    case APP_CALCULATOR: calculator(os); break;
    case APP_FLASHLIGHT: flashlight(os); break;
    case APP_FINANCES: finances(os); break;
    case APP_CHRONOGRAPH: chronograph(os); break;
    case APP_COUNTDOWN: countdown(os); break;
    case APP_CALENDAR: calendar(os); break;
    case APP_GAMES: games(os); break;
    case APP_CONTROLLER: controller(os); break;
    case APP_TODO: todo(os); break;
    default: menu(os); break;
  }
  Serial.write(os->arduboy->getBuffer(), 128 * 64 / 8);
}
