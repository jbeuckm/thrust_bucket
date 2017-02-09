#include "CalibrationMode.h"


CalibrationMode::CalibrationMode(HX711 _scale, rgb_lcd _lcd) : BaseMode(_scale, _lcd) {

  calibration_factor = -7050;

  FUNCTION_COUNT = 3;
}

void CalibrationMode::startMode() {

  scale.set_scale(calibration_factor);

  lcd.setRGB(0, 255, 0);
  lcd.print(F("Calibrating..."));
  
}

void CalibrationMode::updateMode() {

  float measured = scale.get_units();

  lcd.setCursor(0,1);  
  lcd.print(measured);

}


void CalibrationMode::handleWheel(int wheelRotation) {
    int new_index = function_index + wheelRotation;
    while (new_index < 0) {
      new_index += FUNCTION_COUNT;
    }
    while (new_index >= FUNCTION_COUNT) {
      new_index -= FUNCTION_COUNT;
    }
    char buffer[10];
    strcpy_P(buffer, (char*)pgm_read_word(&(calibration_function[new_index])));
    function_index = new_index;
    lcd.setCursor(8,1);
    lcd.print(buffer);
}
