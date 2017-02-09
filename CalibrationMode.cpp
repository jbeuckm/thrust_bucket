#include "CalibrationMode.h"
#include "TareModeFunction.h"


CalibrationMode::CalibrationMode(HX711 _scale, rgb_lcd _lcd) : BaseMode(_scale, _lcd) {
  
  modeFunction = new TareModeFunction(_scale, _lcd);

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




