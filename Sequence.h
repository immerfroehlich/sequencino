
#include "midi_Defs.h"
#include "MidiCommand.h"

#pragma once

class Sequence {

	private:
		struct MidiCommand sequence[32];
		int step;
		int maxSteps;
		int state; //1=record; 2=playback

		void setupMelody();


	public:
		Sequence();
		void nextStep();
		void resetRecordState();
		void resetPlaybackState();

		MidiCommand getCurrentMidiCommand();
		void setCurrentMidiCommand(MidiCommand);
};
