#include "rgb_lcd.h"
#include "HX711.h"

#ifndef BASE_MODE
#define BASE_MODE

class BaseMode {

protected:
  char* function_names[];
  int FUNCTION_COUNT;
  int function_index;

  HX711 scale;
  rgb_lcd lcd;

public:
  BaseMode(HX711 _scale, rgb_lcd _lcd);
  virtual void startMode() = 0;
  virtual void updateMode() = 0;
  virtual void handleWheel(int wheelRotation) = 0;

};

#endif
