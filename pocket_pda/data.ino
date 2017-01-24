#include "data.h"

static void EEPROMWritelong(int address, unsigned long value) {
  unsigned char four = (value & 0xff);
  unsigned char three = ((value >> 8) & 0xff);
  unsigned char two = ((value >> 16) & 0xff);
  unsigned char one = ((value >> 24) & 0xff);
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

static unsigned long EEPROMReadlong(long address) {
  unsigned long four = EEPROM.read(address);
  unsigned long three = EEPROM.read(address + 1);
  unsigned long two = EEPROM.read(address + 2);
  unsigned long one = EEPROM.read(address + 3);
  return ((four << 0) & 0xff) + ((three << 8) & 0xffff) + ((two << 16) & 0xffffff) + ((one << 24) & 0xffffffff);
}

Operation::Operation() {
}

void load(Operation* o) {
}

void save(Operation* o) {
}
