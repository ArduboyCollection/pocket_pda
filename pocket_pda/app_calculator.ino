#include "logic.h"

typedef void (* ButtonClickedEventHandler)(PdaOS*, AppCalculator*);

static void clear(AppCalculator* app) {
  app->opcode2 = "";
  app->opcode1 = "";
  app->opcode0 = "";
  app->operand3 = 0;
  app->operand2 = 0;
  app->operand1 = 0;
  app->operand0 = "0";
  app->dotClicked = false;
  app->numClicked = false;
  //app->txtOpcode = app->opcode0;
  app->txtResult = app->operand0;
}

static double eval(double l, double r, const String &op) {
  if (op == "+") return l + r;
  else if (op == "-") return l - r;
  else if (op == "*") return l * r;
  else if (op == "/") return l / r;
  return 0;
}

static void onLowPriOpClicked(AppCalculator* app, const String &op) {
  if (app->opcode0 == "") {
    app->dotClicked = false;
    app->operand1 = toDouble(app->operand0);
    app->operand0 = "0";
    app->opcode0 = op;
  } else if (app->opcode0 == "+" || app->opcode0 == "-") {
    if (app->numClicked) {
      app->numClicked = false;
      app->dotClicked = false;
      app->operand1 = eval(app->operand1, toDouble(app->operand0), app->opcode0);
      app->operand0 = "0";
      toString(app->operand1, app->txtResult);
      app->opcode0 = op;
    } else {
      app->opcode0 = op;
    }
  } else if (app->opcode0 == "*" || app->opcode0 == "/") {
    if (app->numClicked) {
      app->numClicked = false;
      app->dotClicked = false;
      app->operand1 = eval(app->operand1, toDouble(app->operand0), app->opcode0);
      app->operand0 = "0";
      if (app->opcode1 != "") {
        app->operand1 = eval(app->operand2, app->operand1, app->opcode1);
        app->opcode1 = "";
      }
      toString(app->operand1, app->txtResult);
      app->opcode0 = op;
    } else {
      app->opcode0 = op;
    }
  }
  //app->txtOpcode = app->opcode0;
}

static void onHighPriOpClicked(AppCalculator* app, const String &op) {
  if (app->opcode0 == "") {
    app->dotClicked = false;
    app->operand1 = toDouble(app->operand0);
    app->operand0 = "0";
    app->opcode0 = op;
  } else if (app->opcode0 == "+" || app->opcode0 == "-") {
    if (app->numClicked) {
      app->numClicked = false;
      app->dotClicked = false;
      app->operand2 = app->operand1;
      app->operand1 = toDouble(app->operand0);
      app->operand0 = "0";
      app->opcode1 = app->opcode0;
      app->opcode0 = op;
    } else {
      app->opcode0 = op;
    }
  } else if (app->opcode0 == "*" || app->opcode0 == "/") {
    if (app->numClicked) {
      app->numClicked = false;
      app->dotClicked = false;
      app->operand1 = eval(app->operand1, toDouble(app->operand0), app->opcode0);
      app->operand0 = "0";
      toString(app->operand1, app->txtResult);
      app->opcode0 = op;
    } else {
      app->opcode0 = op;
    }
  }
  //app->txtOpcode = app->opcode0;
}

static void onButtonNumClicked(PdaOS* os, AppCalculator* app, char n) {
  app->numClicked = true;
  if (app->operand0 == "0")
    app->operand0 = "";
  app->operand0 += n;
  app->txtResult = app->operand0;
}

static void onButton0Clicked(PdaOS* os, AppCalculator* app) {
  app->numClicked = true;
  if (app->operand0 != "0")
    app->operand0 += '0';
  app->txtResult = app->operand0;
}

static void onButton1Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '1');
}

static void onButton2Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '2');
}

static void onButton3Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '3');
}

static void onButton4Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '4');
}

static void onButton5Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '5');
}

static void onButton6Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '6');
}

static void onButton7Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '7');
}

static void onButton8Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '8');
}

static void onButton9Clicked(PdaOS* os, AppCalculator* app) {
  onButtonNumClicked(os, app, '9');
}

static void onButtonDotClicked(PdaOS* os, AppCalculator* app) {
  app->numClicked = true;
  if (app->dotClicked)
    return;
  app->operand0 += '.';
  app->txtResult = app->operand0;
  app->dotClicked = true;
}

static void onButtonAddClicked(PdaOS* os, AppCalculator* app) {
  onLowPriOpClicked(app, "+");
}

static void onButtonMinClicked(PdaOS* os, AppCalculator* app) {
  onLowPriOpClicked(app, "-");
}

static void onButtonMulClicked(PdaOS* os, AppCalculator* app) {
  onHighPriOpClicked(app, "*");
}

static void onButtonDivClicked(PdaOS* os, AppCalculator* app) {
  onHighPriOpClicked(app, "/");
}

static void onButtonEvalClicked(PdaOS* os, AppCalculator* app) {
  if (app->opcode0 != "") {
    app->dotClicked = false;
    app->numClicked = false;
    app->operand3 = toDouble(app->operand0);
    app->opcode2 = app->opcode0;
    app->operand1 = eval(app->operand1, toDouble(app->operand0), app->opcode0);
    app->opcode0 = "";
    if (app->opcode1 != "") {
      app->operand1 = eval(app->operand2, app->operand1, app->opcode1);
      app->opcode1 = "";
    }
  } else {
    if (app->opcode2 != "") {
      app->operand1 = eval(app->operand1, app->operand3, app->opcode2);
    }
  }
  toString(app->operand1, app->operand0);
  //app->txtOpcode = app->opcode0;
  app->txtResult = app->operand0;
}

static void onButtonClearClicked(PdaOS* os, AppCalculator* app) {
  clear(app);
}

static void onButtonReverseClicked(PdaOS* os, AppCalculator* app) {
  if (app->operand0 == "0")
      return;
  if (app->operand0.length() != 0 && app->operand0.startsWith("-"))
    app->operand0 = app->operand0.substring(1);
  else
    app->operand0 = "-" + app->operand0;
  app->txtResult = app->operand0;
}

static void onButtonPercentageClicked(PdaOS* os, AppCalculator* app) {
  app->numClicked = true;
  if (app->operand0 == "0")
      return;
  toString(eval(toDouble(app->operand0), 100, "/"), app->operand0);
  app->txtResult = app->operand0;
}

static void onButton00Clicked(PdaOS* os, AppCalculator* app) {
  app->numClicked = true;
  if (app->operand0 != "0")
      app->operand0 += "00";
  app->txtResult = app->operand0;
}

static void update(PdaOS* os, AppCalculator* app) {
  const ButtonClickedEventHandler handlers[] = {
    onButton7Clicked, onButton8Clicked, onButton9Clicked, onButtonDivClicked, onButtonClearClicked,
    onButton4Clicked, onButton5Clicked, onButton6Clicked, onButtonMulClicked, onButtonReverseClicked,
    onButton1Clicked, onButton2Clicked, onButton3Clicked, onButtonMinClicked, onButtonPercentageClicked,
    onButton0Clicked, onButtonDotClicked, onButtonEvalClicked, onButtonAddClicked, onButton00Clicked
  };
  switch (input()) {
    case LEFT_BUTTON:
      if (--app->cursor.x < 0) app->cursor.x = 4;
      break;
    case RIGHT_BUTTON:
      if (++app->cursor.x > 4) app->cursor.x = 0;
      break;
    case UP_BUTTON:
      if (--app->cursor.y < 0) app->cursor.y = 3;
      break;
    case DOWN_BUTTON:
      if (++app->cursor.y > 3) app->cursor.y = 0;
      break;
    case A_BUTTON:
      handlers[app->cursor.x + app->cursor.y * 5](os, app);
      if (app->txtResult.length() > 18) {
        clear(app);
        app->txtResult = "E";
      }
      break;
    case B_BUTTON:
      if (app->opcode0 == "" && (app->operand0 == "" || app->operand0 == "0")) { app->exit(); os->app = -os->app; }
      else { clear(app); }
      break;
  }
}

static void draw(PdaOS* os, AppCalculator* app) {
  os->arduboy->drawRect(5, 5, 118, 13, WHITE);
  os->arduboy->setCursor(8, 8);
  os->arduboy->print(app->txtResult);
  const char CHARS[] = {
    '7', '8', '9', '/', 'C',
    '4', '5', '6', '*', '_',
    '1', '2', '3', '-', '%',
    '0', '.', '=', '+', '#'
  };
  const uint8_t x = 10, y = 20;
  const uint8_t w = 20, h = 9;
  const uint8_t ix = 2, iy = 2;
  for (uint8_t j = 0; j < 4; ++j) {
    for (uint8_t i = 0; i < 5; ++i) {
      char c = CHARS[i + j * 5];
      if (c == '_') {
        os->arduboy->setCursor(x + i * (w + ix) + 1, y + j * (h + iy) + 1);
        os->arduboy->print("-/+");
      } else if (c == '#') {
        os->arduboy->setCursor(x + i * (w + ix) + 4, y + j * (h + iy) + 1);
        os->arduboy->print("00");
      } else {
        os->arduboy->setCursor(x + i * (w + ix) + 7, y + j * (h + iy) + 1);
        os->arduboy->write(c);
      }
      os->arduboy->drawRect(x + i * (w + ix), y + j * (h + iy), w, h, WHITE);
    }
  }
  os->arduboy->drawRect(x + app->cursor.x * (w + ix) - 1, y + app->cursor.y * (h + iy) - 1, w + 2, h + 2, WHITE);
}

void app_calculator(PdaOS* os) {
  AppCalculator* app = &os->calc;
  update(os, app);
  draw(os, app);
}
