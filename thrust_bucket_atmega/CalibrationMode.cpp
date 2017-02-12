#include <EEPROM.h>
#include <math.h>

#include "CalibrationMode.h"
#include "TareModeFunction.h"
#include "CalibrateModeFunction.h"
#include "ChangeModeFunction.h"

CalibrationMode::CalibrationMode(HX711 *_scale, rgb_lcd *_lcd): BaseMode(_scale, _lcd) {

  scale = _scale;
  lcd = _lcd;
  functionIndex = 0;

  EEPROM.get(0, calibration_factor);
  
  if (isnan(calibration_factor)) {
    calibration_factor = -7050;
    EEPROM.put(0, calibration_factor);
    Serial.print(F("saved calibration factor "));
    Serial.println(calibration_factor);
  } else {
    Serial.print(F("loaded calibration factor "));
    Serial.println(calibration_factor);
  }

  scale->set_scale(calibration_factor);
  scale->tare();
//  long zero_factor = scale->read_average(); //Get a baseline reading


  FUNCTION_COUNT = 3;

  modeFunctions = (BaseModeFunction **) malloc(FUNCTION_COUNT * sizeof(BaseModeFunction*));
  
  modeFunctions[0] = new TareModeFunction(scale, lcd);
  modeFunctions[1] = new CalibrateModeFunction(scale, lcd);
  modeFunctions[2] = new ChangeModeFunction(F("[FIRE ]"), 1);

  Serial.println(F("CalibrationMode() complete"));
}

void CalibrationMode::startMode() {

	BaseMode::startMode();

	lcd->clear();
	lcd->setRGB(0, 255, 0);
	lcd->print(F("Calibrating..."));
}


int CalibrationMode::updateMode() {
  Serial.println(F("updateMode()")); 

  float measured = scale->get_units();

  lcd->setCursor(0,1);  
  lcd->print(measured);

  Serial.println(F("updateMode() complete"));

  return modeFunctions[functionIndex]->getChangeModeRequest();
}




