/*
 * CountdownMode.h
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#ifndef COUNTDOWNMODE_H_
#define COUNTDOWNMODE_H_

#include "BaseMode.h"

#define SPEAKER_PIN 5

class CountdownMode: public BaseMode {
private:
	unsigned long timestamp = 0;
	int frequency = 0;


public:
	CountdownMode(HX711 *_scale, rgb_lcd *_lcd);
	virtual void startMode();
	virtual int updateMode();
};

#endif /* COUNTDOWNMODE_H_ */
