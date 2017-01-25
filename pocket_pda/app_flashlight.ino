#include "logic.h"

static void update(PdaOS* os, AppFlashlight* app) {
  if (!app->always) {
    if (++app->tick >= app->interval) app->tick = 0;
  }
  switch (input()) {
    case UP_BUTTON:
      app->interval += 5;
      if (app->interval > 300) app->interval = 300;
      break;
    case DOWN_BUTTON:
      app->interval -= 5;
      if (app->interval <= 0) app->interval = 5;
      break;
    case A_BUTTON:
      app->always = !app->always;
      app->tick = 0;
      break;
    case B_BUTTON:
      app->exit(); os->app = -os->app;
      break;
  }
}

static void draw(PdaOS* os, AppFlashlight* app) {
  if (app->always) {
    os->arduboy->fillRect(0, 0, 128, 64, WHITE);
    os->arduboy->setTextColor(BLACK);
    os->arduboy->setTextBackground(WHITE);
    os->arduboy->setCursor(7, 28);
    os->arduboy->print("'A' to toggle flash");
  } else {
    if (app->tick > app->interval / 2) {
      os->arduboy->fillRect(0, 0, 128, 64, WHITE);
      os->arduboy->setTextColor(BLACK);
      os->arduboy->setTextBackground(WHITE);
      os->arduboy->setCursor(22, 24);
      os->arduboy->print("'UP'/'DOWN' to");
      os->arduboy->setCursor(19, 32);
      os->arduboy->print("modify interval");
    } else {
      os->arduboy->setCursor(22, 24);
      os->arduboy->print("'UP'/'DOWN' to");
      os->arduboy->setCursor(19, 32);
      os->arduboy->print("modify interval");
    }
  }
  os->arduboy->setTextColor(WHITE);
  os->arduboy->setTextBackground(BLACK);
}

void app_flashlight(PdaOS* os) {
  AppFlashlight* app = &os->light;
  update(os, app);
  draw(os, app);
}
