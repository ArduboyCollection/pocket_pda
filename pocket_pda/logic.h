#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "data.h"

double toDouble(const String &str);
void toString(double n, String &ret);
uint8_t input(uint8_t* r = 0);
void initLogic(PdaOS* os);
void run(PdaOS* os);

#endif /* __LOGIC_H__ */
