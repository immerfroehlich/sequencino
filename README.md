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
But that is only temporary.
The midi input schematic is based upon the "Send and Receive MIDI with Arduino"
instructable tutorial by amandaghassaei:
http://www.instructables.com/id/Send-and-Receive-MIDI-with-Arduino/?ALLSTEPS
And the Arudino schematic is based upon the "Arduino on a breadboard" article
https://www.arduino.cc/en/Main/Standalone but without the power regulation
and the usb to serial modules, because the power comes from a regulated
power supply already.

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


Recipe
========================================
TODO: Tranlation needed

For Arduino Module
------------------
- 1x Atmel Atmega 328P- PU, DIL-28 (http://www.reichelt.de/Atmel-ATMega-AVRs/ATMEGA-328P-PU/3/index.html?ACTION=3&GROUPID=2959&ARTICLE=119685&SEARCH=ATMEGA%20328P-PU&OFFSET=16&WKID=0&)
- 1x 1N 4148 Schaltdiode 100V, 0,15A (http://www.reichelt.de/1N-UF-AA-Dioden/1N-4148/3/index.html?ACTION=3&GROUPID=2987&ARTICLE=1730&SEARCH=1N%204148&OFFSET=16&WKID=0&)
- 2x Kerko 22P Kondensator (http://www.reichelt.de/Scheiben/KERKO-22P/3/index.html?ACTION=3&GROUPID=3169&ARTICLE=9281&SEARCH=KERKO%2022P&OFFSET=16&WKID=0&)
- Standard- Quarz 16 MHz HC49/U-S (http://www.reichelt.de/Quarze/16-0000-HC49U-S/3/index.html?ACTION=3&GROUPID=3173&ARTICLE=32852&SEARCH=16%2C0000-HC49U-S&OFFSET=16&WKID=0&)

For controller module
----------------------
- 2x Taster Fritzing Starter Kit
- 2x Drehwiderstand Fritzing Starter Kit
- Widerstände (Resistors)

For midi modules
----------------------
- 2x DIN Midi Stecker
- 1x Optokoppler 6N 138, DIP 8 (http://www.reichelt.de/Optokoppler/6N-138/3/index.html?ACTION=3&GROUPID=3046&ARTICLE=2859&SEARCH=6N%20138&OFFSET=16&WKID=0&)
- Diode 1N 4148 (http://www.reichelt.de/1N-UF-AA-Dioden/1N-4148/3/index.html?ACTION=3&GROUPID=2987&ARTICLE=1730&SEARCH=1n%204148&OFFSET=16&WKID=0&)

Anything else
----------------------
- 1x Lumberg Einbaukupplung DIN45323 (http://www.reichelt.de/Hohlstecker/LUM-NEB-1R/3/index.html?ACTION=3&GROUPID=3258&ARTICLE=116267&SEARCH=LUM%20NEB%201R&OFFSET=16&WKID=0&)
- Kabel (Litze) 0,22^2, 4x5m (http://www.pollin.de/shop/dt/MTI2OTkxOTk-/Haustechnik/Kabel_Draehte_Litzen/Litzen/Litzen_Sortiment_0_22_mm_4x_5_m.html)

Optional (for the ease of use)
----------------------
- 1x GS 28-S :: IC-Sockel, 28-polig, doppelter Federkontakt (http://www.reichelt.de/IC-Sockel/GS-28-S/3/index.html?ACTION=3&GROUPID=7429&ARTICLE=86281&OFFSET=500&)
- 1x Streifenrasterplatine auf Hartpapier fuer Schaltungsaufbau (z.B. https://www.reichelt.de/streifenrasterplatine-hartpapier-50x100mm-h25sr050-p8275.html?&trstct=pol_3)

Relase Notes
=======================
Version 1.0.0:
----------------
Finished working single track recording and playback with tempo poti.
