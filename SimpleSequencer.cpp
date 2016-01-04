// Do not remove the include below
#include "SimpleSequencer.h"

#include "StopWatch.h"

#include "Sequence.h"

#include "MIDI.h"

MIDI_CREATE_DEFAULT_INSTANCE();

StopWatch stopwatch = StopWatch();

Sequence sequence = Sequence();

//struct MidiCommand sequence[32];

const int stepLed1 = 6;
const int stepLed2 = 7;
const int stepLed3 = 8;
const int stepLed4 = 9;
const int stepLed5 = 10;
const int stepLed6 = 11;
const int stepLed7 = 12;
const int stepLed8 = 13;

const int modeLed1 = 3;
const int modeLed2 = 4;
const int modeLed3 = 5;

const int tempoPoti = A2; // Analog A2
int tempoPotiPosition;

const int playButton = A0;
const int recordButton = A1;

const byte NOTE_ON = 144;
//const byte NOTE_ON = 0x90;
const byte NOTE_OFF = 128;
//const byte NOTE_OFF = 0x80;


int step = 0;

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

	pinMode(modeLed1, OUTPUT);
	pinMode(modeLed2, OUTPUT);
	pinMode(modeLed3, OUTPUT);

	//pinMode(button1, INPUT);
	//pinMode(button2, INPUT);
	pinMode(tempoPoti, INPUT);

	pinMode(playButton, INPUT);
	pinMode(recordButton, INPUT);

	MIDI.begin();


	//Serial.begin(31250); //Baudrate for Midi
	//Serial.begin(9600); //Baudrate for Serial communication = Debugging
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

boolean playState = false;
boolean recordState = false;
boolean lastPlayButtonState = false;
boolean lastRecordButtonState = false;

void loop(){
	boolean playPressed = analogRead(playButton) > 500 ? true : false;
	//boolean playPressed = digitalRead(playButton); 
	
	boolean recordPressed = analogRead(recordButton) > 500 ? true : false;
	//boolean recordPressed = digitalRead(recordButton);  
	if(playPressed && (playPressed != lastPlayButtonState)) {
		playState = !playState;
		recordState = false;
		digitalWrite(modeLed2, LOW);
		digitalWrite(modeLed1, HIGH);
		sequence.resetPlaybackState();
	}
	if(recordPressed && (recordPressed != lastRecordButtonState)) {
		recordState = !recordState;
		playState = false;
		digitalWrite(modeLed1, LOW);
		digitalWrite(modeLed2, HIGH);
		sequence.resetRecordState();
		stopwatch.reset();
		stopwatch.start();
	}
	lastPlayButtonState = playPressed;
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


//	if(Serial.available() > 2) {
//		Serial.write(Serial.read());
//		Serial.write(Serial.read());
//		Serial.write(Serial.read());
//	}
}

void record(){
	if (MIDI.read()) {               // Is there a MIDI message incoming ?
		unsigned int length = stopwatch.elapsed();
		sequence.nextStep();

		//Wird das hier erzeugte MidiCommand wieder aufgeräumt?
		MidiCommand command = {MIDI.getType(), MIDI.getData1(), MIDI.getData2(), length};
		sequence.setCurrentMidiCommand(command);
		stopwatch.reset();
		stopwatch.start();

		sendMidiCommand(command);
	}
}

/**
 * Play
 **/
void play() {
//	int potiValue = analogRead(tempoPoti);
//	unsigned int calculatedDelay = calcDelay(potiValue);

	MidiCommand command = sequence.getCurrentMidiCommand();

	if(stopwatch.isRunning() && command.length > stopwatch.elapsed()) {
		//Serial.write(" StopWatch Hold ");
		return;
	}

	//nextLed(currentStep, lastStep);
	//int sequenceStep = currentStep * 2;
	stopwatch.reset();
	stopwatch.start();

	//Serial.write("Write Command");
	sendMidiCommand(command);
	//Serial.write(currentStep);
}

int calcDelay(int potiValue) {
	return map(potiValue, 0, 1023, 40, 1000);

	//40 * log(x*10) -160
	//int returnVal = 40 * log(potiValue*10+50) - 160;
	//return returnVal < 0 ? 0 : returnVal;


	//  int potiPercent = ((float)potiValue / (float)1023) * 100;
	//
	//  int tempoValue = (1000 / 100) * potiPercent + 50;
	//  return tempoValue;
}
