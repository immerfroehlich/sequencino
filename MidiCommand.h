/*
 * MidiCommand.h
 *
 *  Created on: 04.01.2016
 *      Author: andreas
 */

#ifndef MIDICOMMAND_H_
#define MIDICOMMAND_H_

#include "midi_Defs.h"

struct MidiCommand {
		  midi::MidiType command;
		  byte param1;
		  byte param2;
		  unsigned int length;
		};


#endif /* MIDICOMMAND_H_ */
