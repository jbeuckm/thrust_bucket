/*
 * AdvanceModeFunction.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#include "AdvanceModeFunction.h"

AdvanceModeFunction::AdvanceModeFunction(String _label, HX711 *_scale, rgb_lcd *_lcd)
	: BaseModeFunction(_scale, _lcd), label(_label) {

}

AdvanceModeFunction::~AdvanceModeFunction() {
}

String AdvanceModeFunction::getLabel() {
	return label;
}
