// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _SimpleSequencer_H_
#define _SimpleSequencer_H_
#include "Arduino.h"
#include "midi_Defs.h"
//add your includes for the project ArduinoTest here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif

void loop();
void setup();
void sendMidiCommand(struct MidiCommand command, byte channel);
void sendMidiCommandParams(byte command, byte param1, byte param2);
void midiThrough();
void record();
void play();
int calcDelay(int potiValue);
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project ArduinoTest here




//Do not add code below this line
#endif /* _ArduinoTest_H_ */
