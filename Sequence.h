
#include "midi_Defs.h"
#include "MidiCommand.h"

#pragma once

class Sequence {

	private:
		struct MidiCommand sequence[50];

		void setupMelody();


	public:
		Sequence();

		void setStep(int step, MidiCommand command);
		MidiCommand getStep(int step);
};
