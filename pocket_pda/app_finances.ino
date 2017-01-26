#include "logic.h"

static void update(PdaOS* os, AppExchange* app) {
  switch (input()) {
    case B_BUTTON:
      app->exit(); os->app = -os->app;
      break;
  }
}

static void draw(PdaOS* os, AppExchange* app) {
  os->arduboy->setCursor(16, 16);
  os->arduboy->print("1 USD = 6.88 CNY");
  os->arduboy->setCursor(16, 24);
  os->arduboy->print("1 EUR = 7.38 CNY");
  os->arduboy->setCursor(16, 32);
  os->arduboy->print("1 GBP = 8.71 CNY");
  os->arduboy->setCursor(16, 40);
  os->arduboy->print("1 AUD = 5.19 CNY");
}

void app_finances(PdaOS* os) {
  AppExchange* app = &os->exchange;
  update(os, app);
  draw(os, app);
}
