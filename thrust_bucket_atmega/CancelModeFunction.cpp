/*
 * CancelModeFunction.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#include "CancelModeFunction.h"

CancelModeFunction::CancelModeFunction(HX711 *_scale, rgb_lcd *_lcd): BaseModeFunction(_scale, _lcd) {
	// TODO Auto-generated constructor stub

}

String CancelModeFunction::getLabel() {
  return F("[Calib]");
}
