#include "Arduino.h"
#include "rgb_lcd.h"
#include "HX711.h"
#include <avr/pgmspace.h>

#ifndef CALIBRATION_MODE
#define CALIBRATION_MODE

const char cm0[] PROGMEM = "[Calib]";
const char cm1[] PROGMEM = "[TARE ]";
const char cm2[] PROGMEM = "[Test!]";
const char* const calibration_function[] PROGMEM = { cm0, cm1, cm2 };

class CalibrationMode {

private:
int CALIBRATION_FUNCTION_COUNT = 3;
int calibration_function_index = 0;

  float calibration_factor;
  HX711 scale;
  rgb_lcd lcd;

public:
  CalibrationMode(HX711 _scale, rgb_lcd _lcd);
  void startMode();
  void updateMode();
  void handleWheel(int wheelRotation);

};

#endif
