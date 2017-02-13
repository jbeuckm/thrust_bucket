#include "CalibrateModeFunction.h"

CalibrateModeFunction::CalibrateModeFunction(HX711 *_scale, rgb_lcd *_lcd) : BaseModeFunction(_scale, _lcd) {
  scale = _scale;
  lcd = _lcd;
  trapWheelRotation = false;
}

String CalibrateModeFunction::getLabel() {
  return F("[Calibr]");
}

void CalibrateModeFunction::handleButtonDown() {
  trapWheelRotation = true;
}

void CalibrateModeFunction::handleButtonUp() {
  trapWheelRotation = false;

  lcd->setCursor(0, 0);
  lcd->print(F("Calibrating..."));
}

void CalibrateModeFunction::handleWheelRotation(int wheelRotation) {

	int newScale = scale->get_scale() + 10 * wheelRotation;

	scale->set_scale(newScale);

	lcd->setCursor(0, 0);
	lcd->print(newScale);
}


