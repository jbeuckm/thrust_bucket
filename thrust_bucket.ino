/*
  This example code uses bogde's excellent library: https://github.com/bogde/HX711
*/
#include <avr/pgmspace.h>

#include <SPI.h>


#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd *lcd;


#include "HX711.h"
#define HX711_DOUT  7
#define HX711_CLK  6 
HX711 *scale;


#include "BaseMode.h"
#include "CalibrationMode.h"
BaseMode *mode;


#include "RotaryEncoder.h"
RotaryEncoder wheel(4);

void buttonDown() {
  mode->handleButtonDown();
}
void buttonUp() {
  mode->handleButtonUp();
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


#include <SD.h>

const int chipSelect = 8;
File thrustDataFile;

void setupSDcard() {
  pinMode(SS, OUTPUT);

  if (!SD.begin(chipSelect)) {
//    Serial.println(F("SD init failed"));
  }

  String thrustFilename = F("thrust.tsv");

  //  SdFile::dateTimeCallback(dateTime);
  thrustDataFile = SD.open(thrustFilename, O_WRITE | O_CREAT | O_TRUNC);

  if (!thrustDataFile) {
//    Serial.print(F("error opening "));
//    Serial.println(thrustFilename);
  }

  thrustDataFile.println(F("millis\tload"));
}




#define SPEAKER_PIN 6
#define IGNITER_PIN A0
#define BUTTON_PIN A1


enum MISSION_STATE {
  CALIBRATION,
  COUNTDOWN,
  FIRE,
  COOLDOWN
};


MISSION_STATE mission_state = CALIBRATION;




void setup() {

  lcd = new rgb_lcd();
  scale = new HX711(HX711_DOUT, HX711_CLK);

  Serial.begin(9600); 
  Serial.println("begin"); 

  scale->set_scale();
  scale->tare(); //Reset the scale to 0

  long zero_factor = scale->read_average(); //Get a baseline reading

  lcd->begin(16, 2);

  mode = new CalibrationMode(scale, lcd);

  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(IGNITER_PIN, OUTPUT);

  setupRotaryEncoder();
  wheel.checkButton();

  mission_state = CALIBRATION;
  mode->startMode();
  Serial.println("setup complete"); 
}




void loop() {
  Serial.println("begin loop"); 

  wheel.checkButton();
 
  if (wheelRotation != 0) {
    mode->handleWheelRotation(wheelRotation);
    wheelRotation = 0;
  }
  
  mode->updateMode();
  
  Serial.println("loop complete"); 
}




unsigned long last_millis = 0;



unsigned long timestamp;
int frequency;

void start_countdown() {
  lcd->setRGB(255, 0, 0);
  lcd->print(F("COUNTDOWN"));

  timestamp = millis();
  mission_state = COUNTDOWN;
}

void countdown_loop() {
  frequency = (millis() - timestamp) % 1000;
  tone(SPEAKER_PIN, 150 + frequency);

  
  lcd->setCursor(0,1);
  lcd->print(150 + frequency);

  if ( (millis() - timestamp) >= 10000) {
    noTone(SPEAKER_PIN);
    begin_firing();
  }

}

void begin_firing() {
  lcd->clear();
  lcd->setRGB(255, 0, 0);
  lcd->print(F("FIRING!!!"));

  timestamp = millis();

  fire_loop();
  digitalWrite(IGNITER_PIN, HIGH);
  mission_state = FIRE;
}

void fire_loop() {
  unsigned long next_millis = millis();

  scale->read();

//  thrustDataFile.print(next_millis - timestamp);
//  thrustDataFile.print("\t");
//  thrustDataFile.println(scale->get_units());

  if ( (next_millis - timestamp) >= 5000) {
    finish_firing();
  }
}


void finish_firing() {

  mission_state = COOLDOWN;
  lcd->clear();
  lcd->setRGB(0, 0, 255);
  lcd->print(F("COOLDOWN"));

  digitalWrite(IGNITER_PIN, LOW);
  fire_loop();

  thrustDataFile.flush();
  thrustDataFile.close();
}


