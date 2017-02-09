#include "BaseModeFunction.h"


BaseModeFunction::BaseModeFunction(HX711 _scale, rgb_lcd _lcd) {
  scale = _scale;
  lcd = _lcd;
}
