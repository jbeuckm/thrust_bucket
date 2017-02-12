/*
 * AdvanceModeFunction.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: joebeuckman
 */

#include "ChangeModeFunction.h"

ChangeModeFunction::ChangeModeFunction(String _label, int _direction)
	: label(_label), direction(_direction) {

}

ChangeModeFunction::~ChangeModeFunction() {
}

String ChangeModeFunction::getLabel() {
	return label;
}
