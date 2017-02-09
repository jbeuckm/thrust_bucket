#include "CalibrationMode.h"

CalibrationMode::CalibrationMode(HX711 _scale, rgb_lcd _lcd) {
  scale = _scale;
  lcd = _lcd;
  calibration_factor = -7050;

  CALIBRATION_FUNCTION_COUNT = 3;
  calibration_function_index = 0;
}

void CalibrationMode::startMode() {

  scale.set_scale(calibration_factor);

  lcd.setRGB(0, 255, 0);
  lcd.print(F("Calibrating..."));
  
}

void CalibrationMode::handleWheel(int wheelRotation) {
    int new_index = calibration_function_index + wheelRotation;
    while (new_index < 0) {
      new_index += CALIBRATION_FUNCTION_COUNT;
    }
    while (new_index >= CALIBRATION_FUNCTION_COUNT) {
      new_index -= CALIBRATION_FUNCTION_COUNT;
    }
    char buffer[10];
    strcpy_P(buffer, (char*)pgm_read_word(&(calibration_function[new_index])));
    calibration_function_index = new_index;
    lcd.setCursor(8,1);  
    lcd.print(buffer);
}
void CalibrationMode::updateMode() {

  float measured = scale.get_units();

  lcd.setCursor(0,1);  
  lcd.print(measured);

}

