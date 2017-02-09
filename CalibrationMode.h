#include "Arduino.h"
#include <avr/pgmspace.h>
#include "BaseMode.h"
#include "BaseModeFunction.h"

#ifndef CALIBRATION_MODE
#define CALIBRATION_MODE

class CalibrationMode : public BaseMode {

private:
  float calibration_factor;
  HX711 scale;
  rgb_lcd lcd;

public:
  CalibrationMode(HX711 _scale, rgb_lcd _lcd);
  void startMode();
  void updateMode();
};

#endif
