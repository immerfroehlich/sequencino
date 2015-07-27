Sequencino
============================================================
The project is inspired by SimplenZAR.
http://www.roebbeling.de/wordpress/?p=85
But with a different requirement.

The goal is to record a sequence through
your midi controller and vary the tempo
and pauses in between the notes.

The hardware schematic is based upon the fritzing
sketch of SimplenZAR:
http://www.roebbeling.de/wordpress/wp-content/uploads/2011/02/simplenZAR.fz_.zip
But that is only temporary. It will be changed very soon
to have a MIDI input.

Fritzing can be downloaded here:
http://fritzing.org/download/

This project uses Eclipse Arduino IDE, because the original
Arduino IDE does not work for a project beyond a 
few simple Arduino basics.

Download V2.3 here:
http://eclipse.baeyens.it/download.php
And Arduino 1.5.x here:
http://arduino.cc/en/Main/Software


Another Needed Infos
========================================
To burn the Arduino bootloader to your Atmega 328P- PU
you need the following Sketch:
https://github.com/WestfW/OptiLoader
Use the Layout from https://www.arduino.cc/en/Tutorial/ArduinoToBreadboard (with external Clock!)
