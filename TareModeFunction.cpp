#include "TareModeFunction.h"

TareModeFunction::TareModeFunction(HX711 *_scale, rgb_lcd *_lcd) : BaseModeFunction(_scale, _lcd) {
}

String TareModeFunction::getLabel() {
  return F("[TARE ]");
}

void TareModeFunction::handleButtonDown() {
  scale->tare();
}


