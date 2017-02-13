/*
 * CountdownMode.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#include "Arduino.h"
#include "CountdownMode.h"
#include "ChangeModeFunction.h"

CountdownMode::CountdownMode(HX711 *_scale, rgb_lcd *_lcd): BaseMode(_scale, _lcd) {

  scale = _scale;
  lcd = _lcd;
  functionIndex = 0;

  pinMode(SPEAKER_PIN, OUTPUT);

  FUNCTION_COUNT = 1;

  modeFunctions = (BaseModeFunction **) malloc(FUNCTION_COUNT * sizeof(BaseModeFunction*));

  modeFunctions[0] = new ChangeModeFunction(F("[Cancel]"), -1);

  Serial.println(F("CountdownMode() complete"));
}


void CountdownMode::startMode() {

	lcd->clear();
	lcd->setRGB(200, 0, 0);
	lcd->print(F("MOVE TO SAFETY"));

	timestamp = millis();

	BaseMode::startMode();
}


int CountdownMode::updateMode() {

	int elapsed = millis() - timestamp;

  frequency = elapsed % 1000;
  tone(SPEAKER_PIN, 150 + frequency);

  lcd->setCursor(0,1);
  lcd->print(10.0 - (float)elapsed/1000.0);

  if ( elapsed >= 10000) {
    noTone(SPEAKER_PIN);
    return 1;
  }

  return modeFunctions[functionIndex]->getChangeModeRequest();
}


