#include "logic.h"

static void modify(PdaOS* os, AppCountdown* app, int8_t d) {
  switch (app->cursor) {
    case 0:
      app->sec += d;
      break;
    case 1:
      app->sec += d * 10;
      break;
    case 2:
      app->sec += d * 60;
      break;
    case 3:
      app->sec += d * 60 * 10;
      break;
    case 4:
      app->sec += d * 60 * 60;
      break;
    case 5:
      app->sec += d * 60 * 60 * 10;
      break;
  }
  if (app->sec < 0 && app->tick != 0) { app->sec = 0; app->tick = 0; }
  else if (app->sec < 0 && app->tick == 0) { app->sec = 0; }
  else if (app->sec > 28800) { app->sec = 28800; app->tick = 0; }
}

static void update(PdaOS* os, AppCountdown* app) {
  switch (input()) {
    case LEFT_BUTTON:
      if (app->paused) {
        if (++app->cursor > 5) app->cursor = 0;
      }
      break;
    case RIGHT_BUTTON:
      if (app->paused) {
        if (app->cursor == 0) app->cursor = 5;
        else --app->cursor;
      }
      break;
    case UP_BUTTON:
      if (app->paused)
        modify(os, app, 1);
      break;
    case DOWN_BUTTON:
      if (app->paused)
        modify(os, app, -1);
      break;
    case A_BUTTON:
      app->paused = !app->paused;
      break;
    case B_BUTTON:
      app->exit(); os->app = -os->app;
      break;
  }
}

static void draw(PdaOS* os, AppCountdown* app) {
  uint8_t hr = app->sec / 60 / 60;
  uint8_t mi = (app->sec - hr * 60 * 60) / 60;
  uint8_t se = (app->sec - hr * 60 * 60 - mi * 60);
  os->arduboy->setCursor(31, 28);
  if (hr < 10) os->arduboy->print(0);
  os->arduboy->print(hr);
  os->arduboy->print(":");
  if (mi < 10) os->arduboy->print(0);
  os->arduboy->print(mi);
  os->arduboy->print(":");
  if (se < 10) os->arduboy->print(0);
  os->arduboy->print(se);
  os->arduboy->print(":");
  if (app->tick < 10) os->arduboy->print(0);
  os->arduboy->print((uint8_t)app->tick);
  if (app->paused) {
    os->arduboy->drawRect(72 - app->cursor * 6 - app->cursor / 2 * 6, 27, 7, 9, WHITE);
  }
}

static void timeup(PdaOS* os, AppCountdown* app) {
  os->app = APP_FLASHLIGHT;
  os->light.init();
  os->light.always = false;
}

void app_update_countdown(PdaOS* os) {
  AppCountdown* app = &os->count;
  if (!app->paused) {
    app->tick -= 100.0f / FPS;
    while (app->tick <= 0.0f) {
      if (app->sec > 0) {
        app->tick += 99.0f;
      } else {
        app->tick = 0;
        app->paused = true;
        timeup(os, app);
        return;
      }
      if (--app->sec <= 0) {
        app->sec = 0;
      }
    }
  }
}

void app_countdown(PdaOS* os) {
  AppCountdown* app = &os->count;
  update(os, app);
  draw(os, app);
}
