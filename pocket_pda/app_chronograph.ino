#include "logic.h"

static void update(PdaOS* os, AppChronograph* app) {
  switch (input()) {
    case A_BUTTON:
      app->paused = !app->paused;
      break;
    case B_BUTTON:
      if (app->paused && (app->sec != 0 || app->tick != 0)) { app->sec = 0; app->tick = 0; }
      else { app->exit(); os->app = -os->app; }
      break;
  }
}

static void draw(PdaOS* os, AppChronograph* app) {
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
}

void app_update_chronograph(PdaOS* os) {
  AppChronograph* app = &os->chronograph;
  if (!app->paused) {
    app->tick += 100.0f / FPS;
    while (app->tick >= 100.0f) {
      app->tick -= 100.0f;
      if (++app->sec >= 60 * 60 * 100)
        app->sec = 0;
    }
  }
}

void app_chronograph(PdaOS* os) {
  AppChronograph* app = &os->chronograph;
  update(os, app);
  draw(os, app);
}
