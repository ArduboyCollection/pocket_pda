#ifndef __DATA_H__
#define __DATA_H__

#include <Arduboy2.h>

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
  APP_GAMES,
  APP_CONTROLLER,
  APP_TODO,
  APP_END
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

  AppFlashlight();
  ~AppFlashlight();
  void init(void);
  void exit(void);
};

struct AppController {
  AppController();
  ~AppController();
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
    AppController ctrl;
  };

  PdaOS();
  ~PdaOS();
};

void load(void);
void save(void);

#endif /* __DATA_H__ */
