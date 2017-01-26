/*
  This example code uses bogde's excellent library: https://github.com/bogde/HX711
  Arduino pin 2 -> HX711 CLK
  3 -> HX711 DOUT
*/
#include <SPI.h>
#include <SD.h>
const int chipSelect = 8;
File thrustDataFile;

void setupSDcard() {
  Serial.println(F("Initting SD..."));
  pinMode(SS, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println(F("SD init failed"));
  }
  Serial.println(F("SD initted"));

  String thrustFilename = F("thrust.tsv");

  //  SdFile::dateTimeCallback(dateTime);
  thrustDataFile = SD.open(thrustFilename, O_WRITE | O_CREAT | O_TRUNC);

  if (!thrustDataFile) {
    Serial.print(F("error opening "));
    Serial.println(thrustFilename);
  }

  thrustDataFile.println(F("millis\tload"));
}


#include "HX711.h"

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

float calibration_factor = -7050;



#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


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

  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);

  lcd.begin(16, 2);

  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(IGNITER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  begin_calibration();
//  start_countdown();

}

unsigned long n;


void begin_calibration() {
  lcd.setRGB(0, 255, 0);
  lcd.print("Calibrating...");
  mission_state = CALIBRATION;
  n = 0;
}

void loop() {

  switch (mission_state) {
    
    case CALIBRATION:
      calibration_loop();
      break;

    case COUNTDOWN:
      countdown_loop();
      break;
    
    case FIRE:
      fire_loop();
      break;
  }

}


void calibration_loop() {

  scale.set_scale(calibration_factor);

  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 1);
  Serial.print(" lbs");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    start_countdown();
  }

  lcd.setCursor(0,1);
  lcd.print(scale.get_units());
}



unsigned long timestamp;
int frequency;

void start_countdown() {
  lcd.setRGB(255, 0, 0);
  lcd.print("COUNTDOWN");

  timestamp = millis();
  mission_state = COUNTDOWN;
}

void countdown_loop() {
  frequency = (millis() - timestamp) % 1000;
  tone(SPEAKER_PIN, 150 + frequency);

  
  lcd.setCursor(0,1);
  lcd.print(150 + frequency);

  if ( (millis() - timestamp) >= 10000) {
    noTone(SPEAKER_PIN);
    begin_firing();
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    begin_calibration();
  }
}

void begin_firing() {
  lcd.setRGB(255, 0, 0);
  lcd.print("FIRING");

  timestamp = millis();

  fire_loop();
  digitalWrite(IGNITER_PIN, HIGH);
  mission_state = FIRE;
}

void fire_loop() {
  thrustDataFile.print(millis() - timestamp);
  thrustDataFile.print("\t");
  thrustDataFile.println(scale.get_units());

  if ( (millis() - timestamp) >= 5000) {
    finish_firing();
  }
}


void finish_firing() {

  digitalWrite(IGNITER_PIN, LOW);
  fire_loop();

  thrustDataFile.flush();
  thrustDataFile.close();

  lcd.setRGB(0, 0, 255);
  lcd.print("COOLDOWN");
  mission_state = COOLDOWN;

  if (digitalRead(BUTTON_PIN) == LOW) {
    begin_calibration();
  }

}


