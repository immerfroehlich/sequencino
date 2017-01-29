/*
 * Button.cpp
 *
 *  Created on: 04.01.2016
 *      Author: andreas
 */

#include "AnalogMomentaryPushButton.h"

void AnalogMomentaryPushButton::initialize(const int pin)  {
	AnalogMomentaryPushButton::pin = pin;
	pinMode(pin, INPUT);
}

bool AnalogMomentaryPushButton::isPressed() {
	return analogRead(AnalogMomentaryPushButton::pin) > 500 ? true : false;
}

/**
 * Should only be called once in a loop.
 * TODO: provide update function.
 */
bool AnalogMomentaryPushButton::isToggled() {
	bool pressed = analogRead(AnalogMomentaryPushButton::pin) > 500 ? true : false;

	bool toggled;
	if(pressed && (pressed != AnalogMomentaryPushButton::lastState)) {
		toggled = true;
	}
	else {
		toggled = false;
	}

	AnalogMomentaryPushButton::lastState = pressed;

	return toggled;
}

