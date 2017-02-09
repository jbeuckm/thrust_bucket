#include "rgb_lcd.h"
#include "HX711.h"

#ifndef BASE_MODE_FUNCTION
#define BASE_MODE_FUNCTION

class BaseModeFunction {
protected:

  HX711 scale;
  rgb_lcd lcd;

public:
  bool trapWheelRotation = false;

  BaseModeFunction(HX711 _scale, rgb_lcd _lcd);

  virtual char *getLabel() = 0;

  virtual void handleWheelRotation(int wheelRotation);
  virtual void handleButtonDown();
  virtual void handleButtonUp();
};

#endif
