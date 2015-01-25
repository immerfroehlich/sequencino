// Do not remove the include below
#include "SimpleSequencer.h"


#include "StopWatch.h"

struct MidiCommand sequence[30];

StopWatch playWatch = StopWatch();
StopWatch recordWatch = StopWatch();

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
const byte NOTE_OFF = 128;


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

	setupMelody();


	Serial.begin(31250); //Baudrate for Midi
	//Serial.begin(9600); //Baudrate for Serial communication = Debugging
}

void setupMelody() {
	sequence[0].command = NOTE_ON;
	sequence[0].param1 = 50;
	sequence[0].param2 = 100;

	sequence[1].command = NOTE_OFF;
	sequence[1].param1 = 50;
	sequence[1].param2 = 100;

	sequence[2].command = NOTE_ON;
	sequence[2].param1 = 52;
	sequence[2].param2 = 100;

	sequence[3].command = NOTE_OFF;
	sequence[3].param1 = 52;
	sequence[3].param2 = 100;

	sequence[4].command = NOTE_ON;
	sequence[4].param1 = 54;
	sequence[4].param2 = 100;

	sequence[5].command = NOTE_OFF;
	sequence[5].param1 = 54;
	sequence[5].param2 = 100;

	sequence[6].command = NOTE_ON;
	sequence[6].param1 = 57;
	sequence[6].param2 = 100;

	sequence[7].command = NOTE_OFF;
	sequence[7].param1 = 57;
	sequence[7].param2 = 100;
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
	sendMidiCommandParams(command.command, command.param1, command.param2);
}

void sendMidiCommandParams(byte command, byte param1, byte param2) {
	Serial.write(command);
	Serial.write(param1);
	Serial.write(param2);
}

//Ein Step sind immer zwei
//Sequence- Commands (Note ein, Note aus)
int lastStep = 3; //lastSequence-1 / 2
int currentStep = 3; //begins with lastStep
boolean playState = false;
boolean recordState = false;
boolean lastPlayButtonState = false;
boolean lastRecordButtonState = false;

void loop() {
	boolean playPressed = analogRead(playButton) > 500 ? true : false;
	boolean recordPressed = analogRead(recordButton) > 500 ? true : false;
	if(playPressed && (playPressed != lastPlayButtonState)) {
		playState = !playState;
		recordState = false;
		playWatch.stop();
		playWatch.reset();
		digitalWrite(modeLed2, LOW);
		digitalWrite(modeLed1, HIGH);
		currentStep = lastStep;
	}
	if(recordPressed && (recordPressed != lastRecordButtonState)) {
		recordState = !recordState;
		playState = false;
		digitalWrite(modeLed1, LOW);
		digitalWrite(modeLed2, HIGH);
		lastStep = -1;
	}
	lastPlayButtonState = playPressed;
	lastRecordButtonState = recordPressed;

	if(playState) {
		play();
	}
	if(recordState) {
		record();
	}
}

void record(){
	while (Serial.available() > 2) {
		byte commandByte = Serial.read();//read first byte
		byte noteByte = Serial.read();//read next byte
		byte velocityByte = Serial.read();//read final byte

		if(commandByte == NOTE_ON || commandByte == NOTE_OFF) {
			lastStep++;
			sequence[lastStep].command = commandByte;
			sequence[lastStep].param1 = noteByte;
			sequence[lastStep].param2 = velocityByte;

			sendMidiCommand(sequence[lastStep]);
		}
	}
}


/**
 * Play
 **/
void play() {
	//  delay(500);
	//  if(playWatch.state() == StopWatch::RESET) {
	//    playWatch.start();
	//  }

	int potiValue = analogRead(tempoPoti);
	unsigned int calculatedDelay = calcDelay(potiValue);

	if(currentStep == lastStep) {
		currentStep = 0;
	}
	else {
		currentStep++;
	}

	//Serial.println(playWatch.elapsed());

	//  if(currentStep != 0 && playWatch.elapsed() < calculatedDelay) {
	//    return;
	//  }
	//  playWatch.reset();
	//  playWatch.start();

	nextLed(currentStep, lastStep);
	int sequenceStep = (currentStep + 1) * 2 - 1;
	sendMidiCommand(sequence[sequenceStep-1]);
	sendMidiCommand(sequence[sequenceStep]);

	delay(calculatedDelay);

	//Serial.println(sequenceStep);


	//Serial.println(potiValue);
	//Serial.println(tempo);
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
