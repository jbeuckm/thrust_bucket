/*
 * CancelModeFunction.h
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#ifndef CANCELMODEFUNCTION_H_
#define CANCELMODEFUNCTION_H_

#include "BaseModeFunction.h"

class CancelModeFunction: public BaseModeFunction {
public:
	String getLabel();
	CancelModeFunction(HX711 *_scale, rgb_lcd *_lcd);
};

#endif /* CANCELMODEFUNCTION_H_ */
