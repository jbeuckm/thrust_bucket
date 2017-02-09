#include "BaseMode.h"

BaseMode::BaseMode(HX711 _scale, rgb_lcd _lcd) {
  scale = _scale;
  lcd = _lcd;
  function_index = 0;
}

void BaseMode::handleButtonDown() {
  modeFunction->handleButtonDown();
}

void BaseMode::handleButtonUp() {
  modeFunction->handleButtonUp();
}

void BaseMode::handleWheelRotation(int wheelRotation) {
  
  if (modeFunction->trapWheelRotation) {
    modeFunction->handleWheelRotation(wheelRotation);
  } else {
  
    int new_index = function_index + wheelRotation;
    while (new_index < 0) {
      new_index += FUNCTION_COUNT;
    }
    while (new_index >= FUNCTION_COUNT) {
      new_index -= FUNCTION_COUNT;
    }
//    char buffer[10];
//    strcpy_P(buffer, (char*)pgm_read_word(&(calibration_function[new_index])));
    lcd.setCursor(8,1);
    lcd.print(modeFunction->getLabel());

    function_index = new_index;
  }
}

