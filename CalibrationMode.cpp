#include "CalibrationMode.h"
#include "TareModeFunction.h"
#include "CalibrateModeFunction.h"


CalibrationMode::CalibrationMode(HX711 _scale, rgb_lcd _lcd) : BaseMode(_scale, _lcd) {
  
  calibration_factor = -7050;


  modeFunctions = (BaseModeFunction **) malloc(3 * sizeof(BaseModeFunction*));
  
  modeFunctions[0] = new TareModeFunction(_scale, _lcd);
  modeFunctions[1] = new CalibrateModeFunction(_scale, _lcd);

  FUNCTION_COUNT = 2;
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




