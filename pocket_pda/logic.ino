#include "logic.h"

static Operation P;

extern void app_update_chronograph(PdaOS* os);
extern void app_update_countdown(PdaOS* os);

extern void app_calculator(PdaOS* os);
extern void app_flashlight(PdaOS* os);
extern void app_finances(PdaOS* os);
extern void app_chronograph(PdaOS* os);
extern void app_countdown(PdaOS* os);
extern void app_calendar(PdaOS* os);
extern void app_games(PdaOS* os);
extern void app_controller(PdaOS* os);
extern void app_todo(PdaOS* os);

static void init(PdaOS* os) {
  switch (os->app) {
    case APP_CALCULATOR: os->calc.init(); break;
    case APP_FLASHLIGHT: os->light.init(); break;
    case APP_FINANCES: os->exchange.init(); break;
    case APP_CHRONOGRAPH: break;
    case APP_COUNTDOWN: break;
    case APP_CALENDAR: os->calendar.init(); break;
	case APP_CONTROLLER: os->ctrl.init(os); break;
    case APP_GAMES: break;
    case APP_TODO: break;
    default: break;
  }
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
      init(os);
      return;
  }
  const uint8_t* const PAGES[] = { SPRITE_MENU0, SPRITE_MENU1 };
  int8_t idx = -app;
  int8_t page = (idx - 1) / 6;
  os->arduboy->drawBitmap(0, 0, PAGES[page], 128, 64, WHITE);
  if (page != 0) os->arduboy->drawBitmap(120, 0, SPRITE_UP, 8, 8, WHITE);
  if (page != countof(PAGES) - 1) os->arduboy->drawBitmap(120, 56, SPRITE_DOWN, 8, 8, WHITE);
  uint8_t x = (idx - 1) % 3;
  uint8_t y = ((idx - 1) / 3) % 2;
  os->arduboy->drawRect(x * 40 + 8, y * 32, 32, 32, WHITE);
}

double toDouble(const String &str) {
  return strtod(str.c_str(), 0);
}

void toString(double n, String &ret) {
  ret = String(n);
}

uint8_t input(uint8_t* r) {
  uint8_t result = 0;
  if (r) *r = 0;
  if (!P.pr && A.pressed(RIGHT_BUTTON)) {
    P.pr = true;
    result += RIGHT_BUTTON;
  } else if (P.pr && A.notPressed(RIGHT_BUTTON)) {
    P.pr = false;
    if (r) *r += RIGHT_BUTTON;
  }
  if (!P.pl && A.pressed(LEFT_BUTTON)) {
    P.pl = true;
    result += LEFT_BUTTON;
  } else if (P.pl && A.notPressed(LEFT_BUTTON)) {
    P.pl = false;
    if (r) *r += LEFT_BUTTON;
  }
  if (!P.pu && A.pressed(UP_BUTTON)) {
    P.pu = true;
    result += UP_BUTTON;
  } else if (P.pu && A.notPressed(UP_BUTTON)) {
    P.pu = false;
    if (r) *r += UP_BUTTON;
  }
  if (!P.pd && A.pressed(DOWN_BUTTON)) {
    P.pd = true;
    result += DOWN_BUTTON;
  } else if (P.pd && A.notPressed(DOWN_BUTTON)) {
    P.pd = false;
    if (r) *r += DOWN_BUTTON;
  }
  if (!P.pa && A.pressed(A_BUTTON)) {
    P.pa = true;
    result += A_BUTTON;
  } else if (P.pa && A.notPressed(A_BUTTON)) {
    P.pa = false;
    if (r) *r += A_BUTTON;
  }
  if (!P.pb && A.pressed(B_BUTTON)) {
    P.pb = true;
    result += B_BUTTON;
  } else if (P.pb && A.notPressed(B_BUTTON)) {
    P.pb = false;
    if (r) *r += B_BUTTON;
  }
  return result;
}

void initLogic(PdaOS* os) {
  os->operation = &P;
  os->chronograph.init();
  os->count.init();
}

void run(PdaOS* os) {
  switch (os->app) {
    case APP_CALCULATOR: app_calculator(os); break;
    case APP_FLASHLIGHT: app_flashlight(os); break;
    case APP_FINANCES: app_finances(os); break;
    case APP_CHRONOGRAPH: app_chronograph(os); break;
    case APP_COUNTDOWN: app_countdown(os); break;
    case APP_CALENDAR: app_calendar(os); break;
	  case APP_CONTROLLER: app_controller(os); break;
    case APP_GAMES: app_games(os); break;
    case APP_TODO: app_todo(os); break;
    default: menu(os); break;
  }
  app_update_chronograph(os);
  app_update_countdown(os);
  Serial.write(os->arduboy->getBuffer(), 128 * 64 / 8);
}
