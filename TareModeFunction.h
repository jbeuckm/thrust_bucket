#include "BaseModeFunction.h"

class TareModeFunction : public BaseModeFunction {
public:
TareModeFunction(HX711 _scale, rgb_lcd _lcd);
  char * getLabel();

  void handleWheelRotation(int wheelRotation);
  void handleButtonDown();
  void handleButtonUp();

};

