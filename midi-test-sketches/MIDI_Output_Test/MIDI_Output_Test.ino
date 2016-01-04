#include <MIDI.h>

#define LED 13

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  pinMode(LED, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OFF);
}

void loop()
{
  digitalWrite(LED, HIGH);
  MIDI.sendNoteOn(60, 127, 1);
  delay(1000);		       
  MIDI.sendNoteOff(60, 0, 1);
  digitalWrite(LED, LOW);
  delay(1000);
}
