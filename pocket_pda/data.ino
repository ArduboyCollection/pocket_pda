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

extern void app_init_controller(PdaOS* os);

Operation::Operation() {
  init();
}

void Operation::init(void) {
  pl = pr = pu = pd = pa = pb = false;
}

AppCalculator::AppCalculator() {
}

AppCalculator::~AppCalculator() {
}

void AppCalculator::init(void) {
  memset(this, 0, sizeof(AppCalculator));
  txtResult = "0";
  opcode0 = opcode1 = opcode2 = operand0 = "";
  operand1 = operand2 = operand3 = 0;
  dotClicked = numClicked = false;
  cursor.x = cursor.y = 0;
}

void AppCalculator::exit(void) {
}

void AppFlashlight::init(void) {
  always = true;
  interval = FPS * 2;
  tick = 0;
}

void AppExchange::init(void) {
  usd = cny = 0;
  index = 0;
  cursor = 0;
}

void AppExchange::exit(void) {
}

void AppFlashlight::exit(void) {
}

void AppChronograph::init(void) {
  sec = 0;
  tick = 0;
  paused = true;
}

void AppChronograph::exit(void) {
}

void AppCountdown::init(void) {
  sec = 60 * 15;
  tick = 0;
  paused = true;
  cursor = 0;
}

void AppCountdown::exit(void) {
}

void AppCalendar::init(void) {
  yr = EEPROMReadlong(600);
  mo = EEPROM.read(604);
  if (yr == 0 || yr == 0xffffffff) yr = 2017;
  if (mo == 0 || mo == 0xff) mo = 1;
}

void AppCalendar::exit(void) {
  EEPROMWritelong(600, yr);
  EEPROM.write(604, mo);
}

void AppController::init(PdaOS* os) {
  app_init_controller(os);
}

void AppController::exit(void) {
}

PdaOS::PdaOS() {
  app = -APP_BEGIN;
}

PdaOS::~PdaOS() {
}

void load(void) {
}

void save(void) {
}
