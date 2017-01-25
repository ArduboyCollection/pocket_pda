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

struct PdaOS {
  Arduboy2* arduboy;
  int8_t app;

  PdaOS();
};

void load(void);
void save(void);

#endif /* __DATA_H__ */
