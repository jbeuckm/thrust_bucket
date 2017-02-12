#include "TareModeFunction.h"

TareModeFunction::TareModeFunction(HX711 *_scale, rgb_lcd *_lcd) : BaseModeFunction(_scale, _lcd) {
  scale = _scale;
  lcd = _lcd;
  trapWheelRotation = false;
}

String TareModeFunction::getLabel() {
  return F("[ TARE ]");
}

void TareModeFunction::handleButtonDown() {
  scale->tare();
}


