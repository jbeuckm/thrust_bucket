/*
 * AdvanceModeFunction.h
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#ifndef ADVANCEMODEFUNCTION_H_
#define ADVANCEMODEFUNCTION_H_

#include "BaseModeFunction.h"

class AdvanceModeFunction: public BaseModeFunction {
private:
	String label;
public:
	AdvanceModeFunction(String _label, HX711 *_scale, rgb_lcd *_lcd);
	virtual ~AdvanceModeFunction();

	String getLabel();
};

#endif /* ADVANCEMODEFUNCTION_H_ */
