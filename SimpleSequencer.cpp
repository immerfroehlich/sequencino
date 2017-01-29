// Do not remove the include below
#include "SimpleSequencer.h"
#include "StopWatch.h"
#include "Sequence.h"
#include "MIDI.h"
#include "AnalogMomentaryPushButton.h"

MIDI_CREATE_DEFAULT_INSTANCE();

StopWatch stopwatch = StopWatch();

Sequence tracks[4];

int step = 7;
int maxSteps = 7;
int state = 2; //1=record; 2=playback

const int stepLed1 = 6;
const int stepLed2 = 7;
const int stepLed3 = 8;
const int stepLed4 = 9;
const int stepLed5 = 10;
const int stepLed6 = 11;
const int stepLed7 = 12;
const int stepLed8 = 13;

const int playLed = 3;
const int recordLed = 4;
const int modeLed3 = 5;

const int tempoPoti = A2; // Analog A2
int tempoPotiPosition;

const int recordButton = A1;

AnalogMomentaryPushButton playButton;

void setup() {
	// set the digital pin for the 8 step leds
	pinMode(stepLed1, OUTPUT);
	pinMode(stepLed2, OUTPUT);
	pinMode(stepLed3, OUTPUT);
	pinMode(stepLed4, OUTPUT);
	pinMode(stepLed5, OUTPUT);
	pinMode(stepLed6, OUTPUT);
	pinMode(stepLed7, OUTPUT);
	pinMode(stepLed8, OUTPUT);

	pinMode(playLed, OUTPUT);
	pinMode(recordLed, OUTPUT);
	pinMode(modeLed3, OUTPUT);

	pinMode(tempoPoti, INPUT);

	playButton.initialize(A0);
	pinMode(recordButton, INPUT);

	MIDI.begin();
}



/**
 * LED and counter
 **/

void nextLed(int currentStep, int lastStep) {

	int ledOffset = stepLed1;

	int lastLed = (currentStep % 8) + ledOffset;
	int led;
	if(currentStep == lastStep) {
		led = ledOffset;
	}
	else {
		led = ( (currentStep + 1) % 8 ) + ledOffset;
	}

	digitalWrite(lastLed, LOW);
	digitalWrite(led, HIGH);
}

void sendMidiCommand(struct MidiCommand command) {
	MIDI.send(command.command, command.param1, command.param2, 1);
}

void sendMidiAllSoundOff() {
	MIDI.sendControlChange(midi::AllSoundOff, 0, 1);
}

void nextStep() {
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

void resetRecordState() {
	step = -1;
	maxSteps = -1;
	state = 1; //record
}

void resetPlaybackState() {
	step = 0;
	state = 2; //playback
}

boolean playState = false;
boolean recordState = false;
boolean lastPlayButtonState = false;
boolean lastRecordButtonState = false;

void loop(){
	
	boolean recordPressed = analogRead(recordButton) > 500 ? true : false;
	//boolean recordPressed = digitalRead(recordButton);  
	if(playButton.isToggled()) {
		playState = !playState;
		recordState = false;
		digitalWrite(recordLed, LOW);
		digitalWrite(playLed, HIGH);
		resetPlaybackState();

		sendMidiAllSoundOff();

		//In HardwareSerial.cpp old flush method cleared the uart buffer
		//_rx_buffer->head = _rx_buffer->tail;
	}
	if(recordPressed && (recordPressed != lastRecordButtonState)) {
		recordState = !recordState;
		playState = false;
		digitalWrite(playLed, LOW);
		digitalWrite(recordLed, HIGH);
		resetRecordState();
		stopwatch.reset();
		stopwatch.start();

		sendMidiAllSoundOff();
	}
	lastRecordButtonState = recordPressed;

	if(playState) {
		play();
	}
	else if(recordState) {
		record();
	}
	else { //Stop State
		midiThrough();
	}
}

void midiThrough() {
	//Midi through is a configuration in the MIDI library
	MIDI.read();

//	if(Serial.available() > 2) {
//		Serial.write(Serial.read());
//		Serial.write(Serial.read());
//		Serial.write(Serial.read());
//	}
}

void record(){
	if (MIDI.read()) {               // Is there a MIDI message incoming ?
		if(MIDI.getType() != midi::NoteOn && MIDI.getType() != midi::NoteOff) {
			return;
		}
		unsigned int length = stopwatch.elapsed();
		nextStep();

		//Just debug stuff
		digitalWrite(stepLed1, HIGH);
		delay(100);
		digitalWrite(stepLed1, LOW);

		//Wird das hier erzeugte MidiCommand wieder aufgeräumt?
		MidiCommand command = {MIDI.getType(), MIDI.getData1(), MIDI.getData2(), length};
		tracks[0].setStep(step, command);
		stopwatch.reset();
		stopwatch.start();

		//sendMidiCommand(command);
	}
}

/**
 * Play
 **/
void play() {
	int potiValue = analogRead(tempoPoti);
	unsigned int calculatedDelay = calcDelay(potiValue);


	if(stopwatch.isRunning() && calculatedDelay > stopwatch.elapsed()) {
		//Serial.write(" StopWatch Hold ");
		return;
	}
	MidiCommand command = tracks[0].getStep(step);

	//nextLed(currentStep, lastStep);
	//int sequenceStep = currentStep * 2;
	nextStep();
	stopwatch.reset();
	stopwatch.start();

	//Serial.write("Write Command");
	sendMidiCommand(command);
	//Serial.write(currentStep);
}

int calcDelay(int potiValue) {
	return map(potiValue, 0, 1023, 20, 500);

	//40 * log(x*10) -160
	//int returnVal = 40 * log(potiValue*10+50) - 160;
	//return returnVal < 0 ? 0 : returnVal;


	//  int potiPercent = ((float)potiValue / (float)1023) * 100;
	//
	//  int tempoValue = (1000 / 100) * potiPercent + 50;
	//  return tempoValue;
}


