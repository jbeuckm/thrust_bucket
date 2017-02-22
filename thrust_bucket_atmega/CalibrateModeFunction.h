#include "BaseModeFunction.h"

#define CALIB_ADJUST_BALLPARK 100
#define CALIB_ADJUST_FINE 1

class CalibrateModeFunction : public BaseModeFunction {

private:
	int adjustmentSize = CALIB_ADJUST_FINE;

public:
  CalibrateModeFunction(HX711 *_scale, rgb_lcd *_lcd);
  String getLabel();

  void handleWheelRotation(int wheelRotation);
  void handleButtonDown();
  void handleButtonUp();
};

