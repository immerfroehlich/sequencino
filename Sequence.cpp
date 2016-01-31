/*
 * Sequence.cpp
 *
 *  Created on: 04.01.2016
 *      Author: andreas
 */

#include "Sequence.h"

Sequence::Sequence()  {
	setupMelody();
	step = 7;
	maxSteps = 7;
	state = 2; //playback

}

void Sequence::setupMelody() {
	sequence[0].command = midi::NoteOn; //D
	sequence[0].param1 = 50;
	sequence[0].param2 = 100;
	sequence[0].length = 2500;

	sequence[1].command = midi::NoteOff;
	sequence[1].param1 = 50;
	sequence[1].param2 = 100;
	sequence[1].length = 1500;

	sequence[2].command = midi::NoteOn; //Eb
	sequence[2].param1 = 51;
	sequence[2].param2 = 100;
	sequence[2].length = 2500;

	sequence[3].command = midi::NoteOff;
	sequence[3].param1 = 51;
	sequence[3].param2 = 100;
	sequence[3].length = 1500;

	sequence[4].command = midi::NoteOn; //E
	sequence[4].param1 = 52;
	sequence[4].param2 = 100;
	sequence[4].length = 2500;

	sequence[5].command = midi::NoteOff;
	sequence[5].param1 = 52;
	sequence[5].param2 = 100;
	sequence[5].length = 1500;

	sequence[6].command = midi::NoteOn; //F
	sequence[6].param1 = 53;
	sequence[6].param2 = 100;
	sequence[6].length = 2500;

	sequence[7].command = midi::NoteOff;
	sequence[7].param1 = 53;
	sequence[7].param2 = 100;
	sequence[7].length = 1500;
}

void Sequence::nextStep() {
	if(state == 1) { //record
		step++;
		maxSteps++;
	}
	else {
		//TODO Durch step++ und if(step > maxSteps) step = 0; ersetzten
		//um ggf den modulo overflow zu beseitigen.
		step = (step + 1) % (maxSteps + 1);
	}
}

void Sequence::resetRecordState() {
	step = -1;
	maxSteps = -1;
	state = 1; //record
}

void Sequence::resetPlaybackState() {
	step = 0;
	state = 2; //playback
}

MidiCommand Sequence::getCurrentMidiCommand() {
	return sequence[step];
}

void Sequence::setCurrentMidiCommand(MidiCommand command) {
	sequence[step] = command;
}


