#include "CalibrateModeFunction.h"

CalibrateModeFunction::CalibrateModeFunction(HX711 _scale, rgb_lcd _lcd) : BaseModeFunction(_scale, _lcd) {
}

String CalibrateModeFunction::getLabel() {
  return F("[Calib]");
}

void CalibrateModeFunction::handleButtonDown() {
  trapWheelRotation = true;
}

void CalibrateModeFunction::handleButtonUp() {
  trapWheelRotation = false;
}

void CalibrateModeFunction::handleWheelRotation(int wheelRotation) {
}


