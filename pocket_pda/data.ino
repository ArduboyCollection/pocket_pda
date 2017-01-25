#include "data.h"

static void EEPROMWritelong(uint16_t address, uint32_t value) {
  uint8_t four = (value & 0xff);
  uint8_t three = ((value >> 8) & 0xff);
  uint8_t two = ((value >> 16) & 0xff);
  uint8_t one = ((value >> 24) & 0xff);
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

static uint32_t EEPROMReadlong(uint16_t address) {
  uint32_t four = EEPROM.read(address);
  uint32_t three = EEPROM.read(address + 1);
  uint32_t two = EEPROM.read(address + 2);
  uint32_t one = EEPROM.read(address + 3);
  return ((four << 0) & 0xff) + ((three << 8) & 0xffff) + ((two << 16) & 0xffffff) + ((one << 24) & 0xffffffff);
}

Operation::Operation() {
  pl = pr = pu = pd = pa = pb = false;
}

PdaOS::PdaOS() {
  app = -APP_BEGIN;
}

void load(void) {
}

void save(void) {
}
