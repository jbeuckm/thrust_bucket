#include <EEPROM.h>

#include "CalibrationMode.h"
#include "TareModeFunction.h"
#include "CalibrateModeFunction.h"
#include <math.h>

CalibrationMode::CalibrationMode(HX711 _scale, rgb_lcd _lcd) : BaseMode(_scale, _lcd) {
  
  EEPROM.get(0, calibration_factor);
  
  if (isnan(calibration_factor)) {
    calibration_factor = -7050;
    EEPROM.put(0, calibration_factor);
  }

  scale.set_scale(calibration_factor);


  modeFunctions = (BaseModeFunction **) malloc(3 * sizeof(BaseModeFunction*));
  
  modeFunctions[0] = new TareModeFunction(_scale, _lcd);
//  modeFunctions[1] = new CalibrateModeFunction(_scale, _lcd);

  FUNCTION_COUNT = 1;
}

void CalibrationMode::startMode() {

  lcd.setRGB(0, 255, 0);
  lcd.print(F("Calibrating..."));

  showFunctionName();
  
}

void CalibrationMode::updateMode() {

  float measured = scale.get_units();

  lcd.setCursor(0,1);  
  lcd.print(measured);

}




