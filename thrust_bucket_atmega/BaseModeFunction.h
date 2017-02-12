#include "arduino.h"
#include "rgb_lcd.h"
#include "HX711.h"

#ifndef BASE_MODE_FUNCTION
#define BASE_MODE_FUNCTION

class BaseModeFunction {
protected:

  HX711 *scale;
  rgb_lcd *lcd;

  int changeModeRequest = 0;

public:
  bool trapWheelRotation;

  BaseModeFunction();
  BaseModeFunction(HX711 *_scale, rgb_lcd *_lcd);

  virtual String getLabel() = 0;

  virtual void handleWheelRotation(int wheelRotation);
  virtual void handleButtonDown();
  virtual void handleButtonUp();

  int getChangeModeRequest();
};

#endif
