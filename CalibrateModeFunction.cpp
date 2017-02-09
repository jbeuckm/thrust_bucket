#include "CalibrateModeFunction.h"

CalibrateModeFunction::CalibrateModeFunction(HX711 _scale, rgb_lcd _lcd) : BaseModeFunction(_scale, _lcd) {
}

char *CalibrateModeFunction::getLabel() {
  return (char *)F("[TARE ]");
}

void CalibrateModeFunction::handleButtonDown() {
  this->trapWheelRotation = true;
}

void CalibrateModeFunction::handleButtonUp() {
  this->trapWheelRotation = false;
}

void CalibrateModeFunction::handleWheelRotation(int wheelRotation) {
}


