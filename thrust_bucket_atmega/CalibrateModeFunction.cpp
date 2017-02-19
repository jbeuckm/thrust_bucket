#include "CalibrateModeFunction.h"

CalibrateModeFunction::CalibrateModeFunction(HX711 *_scale, rgb_lcd *_lcd) :
		BaseModeFunction(_scale, _lcd) {
	scale = _scale;
	lcd = _lcd;
	trapWheelRotation = false;
}

String CalibrateModeFunction::getLabel() {
	return F("[Calibr]");
}

void CalibrateModeFunction::handleButtonDown() {

	if (trapWheelRotation) {
		trapWheelRotation = false;
		lcd->setCursor(0, 0);
		lcd->print(F("Calibrating..."));
	} else {
		trapWheelRotation = true;
		adjustmentSize = CALIB_ADJUST_BALLPARK;
	}
}

void CalibrateModeFunction::handleButtonUp() {
	adjustmentSize = CALIB_ADJUST_FINE;
}

void CalibrateModeFunction::handleWheelRotation(int wheelRotation) {

	int newScale = scale->get_scale() + adjustmentSize * wheelRotation;

	scale->set_scale(newScale);

	lcd->setCursor(0, 0);
	lcd->print(newScale);
	lcd->print("  ");
}

