/*
 * IgniteMode.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#include "IgniteMode.h"
#include "CancelModeFunction.h"

void IgniteMode::setupSDcard() {
  pinMode(SS, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println(F("SD init failed"));
  }

  String thrustFilename = F("thrust.tsv");

//  SdFile::dateTimeCallback(dateTime);
  thrustDataFile = SD.open(thrustFilename, O_WRITE | O_CREAT | O_TRUNC);

  if (!thrustDataFile) {
    Serial.print(F("error opening "));
    Serial.println(thrustFilename);
  }

  thrustDataFile.println(F("millis\tload"));
}


IgniteMode::IgniteMode(HX711 *_scale, rgb_lcd *_lcd): BaseMode(_scale, _lcd) {
	  scale = _scale;
	  lcd = _lcd;
	  function_index = 0;

	  FUNCTION_COUNT = 1;

	  modeFunctions = (BaseModeFunction **) malloc(FUNCTION_COUNT * sizeof(BaseModeFunction*));

	  modeFunctions[0] = new CancelModeFunction(scale, lcd);

	  Serial.println(F("CalibrationMode() complete"));

}



void IgniteMode::startMode() {
	lcd->clear();
	lcd->setRGB(255, 0, 0);
	lcd->print(F("FIRING!!!"));

	timestamp = millis();

	digitalWrite(IGNITER_PIN, HIGH);
}


void IgniteMode::updateMode() {

  unsigned long next_millis = millis();

  thrustDataFile.print(next_millis - timestamp);
  thrustDataFile.print("\t");
  thrustDataFile.println(scale->get_units());

  if ( (next_millis - timestamp) >= 5000) {
    finish();
  }
}


void IgniteMode::finish() {

  lcd->clear();
  lcd->setRGB(0, 0, 255);
  lcd->print(F("COOLDOWN"));

  digitalWrite(IGNITER_PIN, LOW);

  thrustDataFile.flush();
  thrustDataFile.close();
}
