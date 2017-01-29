
#include "Arduino.h"


#pragma once

class AnalogMomentaryPushButton {

	private:
		int pin;
		boolean state = false;
		boolean lastState = false;
		boolean pressed = false;


	public:
		void initialize(const int pin);

		bool isPressed();
		bool isToggled();
};
