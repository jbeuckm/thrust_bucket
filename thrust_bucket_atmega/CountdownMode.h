/*
 * CountdownMode.h
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#ifndef COUNTDOWNMODE_H_
#define COUNTDOWNMODE_H_

#include "BaseMode.h"
#include "CancelModeFunction.h"

#define SPEAKER_PIN 5

class CountdownMode: public BaseMode {
private:
	unsigned long timestamp;
	int frequency;


public:
	CountdownMode(HX711 *_scale, rgb_lcd *_lcd);
	virtual void startMode();
	virtual void updateMode();
};

#endif /* COUNTDOWNMODE_H_ */
