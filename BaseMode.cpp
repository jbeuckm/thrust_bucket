#include "BaseMode.h"

BaseMode::BaseMode(HX711 _scale, rgb_lcd _lcd) {
  scale = _scale;
  lcd = _lcd;
  function_index = 0;
}

void BaseMode::handleButtonDown() {
}

void BaseMode::handleButtonUp() {
}
