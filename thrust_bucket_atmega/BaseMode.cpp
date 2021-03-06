#include "BaseMode.h"

BaseMode::BaseMode(HX711 *_scale, rgb_lcd *_lcd) {
  scale = _scale;
  lcd = _lcd;
  functionIndex = 0;
}

void BaseMode::zeroModeChangeRequests() {
	for (int i=0; i<FUNCTION_COUNT; i++) {
		modeFunctions[i]->setChangeModeRequest(0);
	}
}


void BaseMode::startMode() {
	zeroModeChangeRequests();
	functionIndex = 0;
	showFunctionName();
}

void BaseMode::handleButtonDown() {
  modeFunctions[functionIndex]->handleButtonDown();
}

void BaseMode::handleButtonUp() {
  modeFunctions[functionIndex]->handleButtonUp();
}

void BaseMode::handleWheelRotation(int wheelRotation) {
  
  if (modeFunctions[functionIndex]->trapWheelRotation) {
    modeFunctions[functionIndex]->handleWheelRotation(wheelRotation);
  } else {
  
    int new_index = functionIndex + wheelRotation;
    while (new_index < 0) {
      new_index += FUNCTION_COUNT;
    }
    while (new_index >= FUNCTION_COUNT) {
      new_index -= FUNCTION_COUNT;
    }

    functionIndex = new_index;
    showFunctionName();

  }
}


void BaseMode::showFunctionName() {
  lcd->setCursor(8,1);
  lcd->print(modeFunctions[functionIndex]->getLabel());
}

