#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-02-11 16:09:45

#include "Arduino.h"
#include <avr/pgmspace.h>
#include <SPI.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include "HX711.h"
#define HX711_DOUT  7
#define HX711_CLK  6
#include "BaseMode.h"
#include "CalibrationMode.h"
#include "RotaryEncoder.h"
#include <SD.h>
void buttonDown() ;
void buttonUp() ;
void rotateWheel(int direction) ;
void setupRotaryEncoder() ;
void interruptA() ;
void interruptB() ;
void setupSDcard() ;
void setup() ;
void loop() ;
void start_countdown() ;
void countdown_loop() ;
void begin_firing() ;
void fire_loop() ;
void finish_firing() ;

#include "thrust_bucket_atmega.ino"


#endif
