/*
 * AdvanceModeFunction.h
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#ifndef CHANGEMODEFUNCTION_H_
#define CHANGEMODEFUNCTION_H_

#include "BaseModeFunction.h"

class ChangeModeFunction: public BaseModeFunction {
private:
	String label;
	int direction;
public:
	ChangeModeFunction(String _label, int _direction);

	String getLabel();
	void handleButtonUp();
};

#endif /* CHANGEMODEFUNCTION_H_ */
