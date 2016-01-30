#include <MIDI.h>

#define LED 13

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  pinMode(LED, OUTPUT);
  MIDI.begin();
}

void loop()
{

  for(int i=50; i<60; i++) {
    digitalWrite(LED, HIGH);
    MIDI.sendNoteOn(i, 127, 1);
    delay(1000);           
    MIDI.sendNoteOff(i, 0, 1);
    digitalWrite(LED, LOW);
    delay(1000);
  }
  
}
