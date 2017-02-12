/*
 * IgniteMode.h
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#ifndef IGNITEMODE_H_
#define IGNITEMODE_H_

#include <SD.h>
#include "BaseMode.h"

#define IGNITER_PIN A0

class IgniteMode: public BaseMode {
private:
	unsigned long timestamp;
	unsigned long last_millis = 0;
	const int chipSelect = 8;
	File thrustDataFile;
	void setupSDcard();
	void finish();

public:
	IgniteMode(HX711 *_scale, rgb_lcd *_lcd);
	virtual void startMode();
	virtual void updateMode();
};

#endif /* IGNITEMODE_H_ */
