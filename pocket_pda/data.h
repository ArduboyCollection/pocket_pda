#ifndef __DATA_H__
#define __DATA_H__

#include <Arduboy2.h>

#ifndef FPS
# define FPS 30
#endif /* FPS */

#ifndef countof
# define countof(A) (sizeof(A) / sizeof(*(A)))
#endif /* countof */

struct Operation {
  bool pl : 1;
  bool pr : 1;
  bool pu : 1;
  bool pd : 1;
  bool pa : 1;
  bool pb : 1;

  Operation();
  void init(void);
};

enum Apps {
  APP_BEGIN = 1,
  APP_CALCULATOR = 1,
  APP_FLASHLIGHT,
  APP_FINANCES,
  APP_CHRONOGRAPH,
  APP_COUNTDOWN,
  APP_CALENDAR,
  APP_CONTROLLER,
  APP_GAMES,
  APP_TODO,
  APP_END = APP_CONTROLLER + 1
};

struct PdaOS;

struct AppCalculator {
  String txtResult;
  String opcode0;
  String opcode1;
  String opcode2;
  String operand0;
  double operand1;
  double operand2;
  double operand3;
  bool dotClicked;
  bool numClicked;
  Point cursor;

  AppCalculator();
  ~AppCalculator();
  void init(void);
  void exit(void);
};

struct AppFlashlight {
  bool always;
  int16_t interval;
  int16_t tick;

  void init(void);
  void exit(void);
};

struct AppExchange {
  double usd;
  double cny;
  uint8_t index;
  uint8_t cursor;

  void init(void);
  void exit(void);
};

struct AppChronograph {
  uint32_t sec;
  float tick;
  bool paused;

  void init(void);
  void exit(void);
};

struct AppCountdown {
  int16_t sec;
  float tick;
  bool paused;
  uint8_t cursor;

  void init(void);
  void exit(void);
};

struct AppCalendar {
  uint32_t yr;
  uint8_t mo;

  void init(void);
  void exit(void);
};

struct AppController {
  void init(PdaOS* os);
  void exit(void);
};

struct PdaOS {
  Arduboy2* arduboy;
  Operation* operation;
  int8_t app;
  union {
    AppCalculator calc;
    AppFlashlight light;
    AppExchange exchange;
    AppController ctrl;
    AppCalendar calendar;
  };
  AppChronograph chronograph;
  AppCountdown count;

  PdaOS();
  ~PdaOS();
};

void load(void);
void save(void);

#endif /* __DATA_H__ */
