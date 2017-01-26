#include "logic.h"

static bool isLeapYear(uint32_t yr) {
  if (yr % 100) return (yr % 400) == 0;
  else return (yr % 4) == 0;
}

static uint8_t getDaysOfMonth(uint32_t yr, uint8_t mo) {
  return (mo == 2) ? (28 + isLeapYear(yr)) : 31 - (mo - 1) % 7 % 2;
}

static uint8_t getDayOfWeek(uint32_t yr, uint8_t mo, uint8_t d) {
  return (d += mo < 3 ? yr-- : yr - 2, 23 * mo / 9 + d + 4 + yr / 4 - yr / 100 + yr / 400) % 7;
}

static void update(PdaOS* os, AppCalendar* app) {
  switch (input()) {
    case LEFT_BUTTON:
      if (--app->yr < 1970) app->yr = 1970;
      break;
    case RIGHT_BUTTON:
      if (++app->yr > 2199) app->yr = 2199;
      break;
    case UP_BUTTON:
      if (++app->mo > 12) {
        if (++app->yr > 2199) { app->yr = 2199; app->mo = 12; }
        else { app->mo = 1; }
      }
      break;
    case DOWN_BUTTON:
      if (--app->mo < 1) {
        if (--app->yr < 1970) { app->yr = 1970; app->mo = 1; }
        else { app->mo = 12; }
      }
      break;
    case A_BUTTON:
      break;
    case B_BUTTON:
      app->exit(); os->app = -os->app;
      break;
  }
}

static void draw(PdaOS* os, AppCalendar* app) {
  uint8_t days = getDaysOfMonth(app->yr, app->mo);
  uint8_t day = getDayOfWeek(app->yr, app->mo, 1);
  os->arduboy->setCursor(40, 0);
  os->arduboy->print(app->yr);
  os->arduboy->print("  ");
  os->arduboy->print(app->mo);
  os->arduboy->setCursor(4, 8);
  os->arduboy->print("SU MO TU WE TH FR SA");
  uint8_t x = day;
  uint8_t y = 0;
  for (uint8_t i = 1; i <= days; ++i) {
    if (i < 10) os->arduboy->setCursor(x * 18 + 4 + 6, y * 8 + 16);
    else os->arduboy->setCursor(x * 18 + 4, y * 8 + 16);
    os->arduboy->print(i);
    if (++x == 7) {
      x = 0;
      ++y;
    }
  }
}

void app_calendar(PdaOS* os) {
  AppCalendar* app = &os->calendar;
  update(os, app);
  draw(os, app);
}
