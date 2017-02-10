#include "BaseModeFunction.h"


BaseModeFunction::BaseModeFunction(HX711 _scale, rgb_lcd _lcd) {
  scale = _scale;
  lcd = _lcd;
  trapWheelRotation = false;
}

void BaseModeFunction::handleWheelRotation(int wheelRotation) {
}
void BaseModeFunction::handleButtonUp() {
}
void BaseModeFunction::handleButtonDown() {
}

