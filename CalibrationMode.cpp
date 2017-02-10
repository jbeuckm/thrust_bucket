#include <EEPROM.h>

#include "CalibrationMode.h"
#include "TareModeFunction.h"
#include "CalibrateModeFunction.h"
#include <math.h>

CalibrationMode::CalibrationMode(HX711 _scale, rgb_lcd _lcd) : BaseMode(_scale, _lcd) {

    Serial.println("CalibrationMode()"); 

  EEPROM.get(0, calibration_factor);
  
  if (isnan(calibration_factor)) {
    calibration_factor = -7050;
    EEPROM.put(0, calibration_factor);
    Serial.print("saved calibration factor ");
    Serial.println(calibration_factor);
  } else {
    Serial.print("loaded calibration factor ");
    Serial.println(calibration_factor);
  }

  scale.set_scale(calibration_factor);


  FUNCTION_COUNT = 2;

  modeFunctions = (BaseModeFunction **) malloc(FUNCTION_COUNT * sizeof(BaseModeFunction*));
  
  modeFunctions[0] = new TareModeFunction(scale, lcd);
  modeFunctions[1] = new CalibrateModeFunction(_scale, _lcd);

    Serial.println("CalibrationMode() complete"); 
}

void CalibrationMode::startMode() {

  lcd.setRGB(0, 255, 0);
  lcd.print(F("Calibrating..."));

  showFunctionName();
  
}

float f = 0.0f;
void CalibrationMode::updateMode() {
    Serial.println("updateMode()"); 

//  float measured = scale.get_units();
  float measured = f;
  f += .01;

  lcd.setCursor(0,1);  
  lcd.print(measured);

    Serial.println("updateMode() complete"); 
}




