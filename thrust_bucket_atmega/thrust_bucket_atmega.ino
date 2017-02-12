/*
  This example code uses bogde's excellent library: https://github.com/bogde/HX711
*/
#include <avr/pgmspace.h>

#include <SPI.h>


#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;


#include "HX711.h"
#define HX711_DOUT  7
#define HX711_CLK  6
HX711 scale(HX711_DOUT, HX711_CLK);


#include "BaseMode.h"
#include "CalibrationMode.h"
#include "CountdownMode.h"
#include "IgniteMode.h"

BaseMode **modes;
int mode_index = 0;

#include "RotaryEncoder.h"
RotaryEncoder wheel(4);

void buttonDown() {
	modes[mode_index]->handleButtonDown();
}
void buttonUp() {
	modes[mode_index]->handleButtonUp();
}

volatile int wheelRotation = 0;

void rotateWheel(int direction) {
  wheelRotation += direction;
}

void setupRotaryEncoder() {
  attachInterrupt(0, interruptA, RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(1, interruptB, RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
  wheel.setHandleButtonDown(buttonDown);
  wheel.setHandleButtonUp(buttonUp);
  wheel.setHandleRotate(rotateWheel);
}

void interruptA() {
  wheel.PinA();
}
void interruptB() {
  wheel.PinB();
}

int NUMBER_OF_MODES = 3;


void setup() {

  Serial.begin(9600);
  Serial.println(F("setup()"));

  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  lcd.begin(16, 2);

  modes = (BaseMode **) malloc(NUMBER_OF_MODES * sizeof(BaseMode*));

  modes[0] = new CalibrationMode(&scale, &lcd);
  modes[1] = new CountdownMode(&scale, &lcd);
  modes[2] = new IgniteMode(&scale, &lcd);


  setupRotaryEncoder();
  wheel.checkButton();

  modes[mode_index]->startMode();
  Serial.println(F("setup complete"));
}



void loop() {
  Serial.println(F("begin loop"));

  wheel.checkButton();

  if (wheelRotation != 0) {
	modes[mode_index]->handleWheelRotation(wheelRotation);
    wheelRotation = 0;
  }

  int changeRequest = modes[mode_index]->updateMode();
  if (changeRequest != 0) {
	  mode_index += changeRequest;
	  while (mode_index >= NUMBER_OF_MODES) mode_index -= NUMBER_OF_MODES;
	  while (mode_index < 0) mode_index += NUMBER_OF_MODES;

	  modes[mode_index]->startMode();
  }

  Serial.println(F("loop complete"));
}


