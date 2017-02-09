#include "TareModeFunction.h"

TareModeFunction::TareModeFunction(HX711 _scale, rgb_lcd _lcd) : BaseModeFunction(_scale, _lcd) {
}

char *TareModeFunction::getLabel() {
  return (char *)F("[TARE ]");
}

void TareModeFunction::handleWheelRotation(int wheelRotation) {
}
void TareModeFunction::handleButtonDown(){
}
void TareModeFunction::handleButtonUp() {
}


