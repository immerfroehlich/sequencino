$fn = 100;

//Measurement is defined in millimeters

printerTolerance = 0.6;
ledRadius = 2.5;
potiRadius = 2.55;
buttonXY = 6;

caseWidth = 120;
caseDepth = 50;
caseHeight = 30;

wallThickness = 5;
inlayThickness = 2.5;
inlayHighness = 5;

midiX = 21.2;
midiZ = 19.5; //y in Draufsicht
midiDistance = 15;

topCase();
//buttomCase();

module buttomCase() {
	buttomZ = 20;

	roomX = caseWidth - (2 * wallThickness);
	roomY = caseDepth - (2 * wallThickness);

	difference(){
		cube([caseWidth, caseDepth, buttomZ]);

		translate([wallThickness, wallThickness, -wallThickness]) {
			cube([roomX, roomY, buttomZ]);
		}

		buttomCaseOuterInlay();
	}
}

module buttomCaseOuterInlay() {
	roomX = caseWidth - (2 * inlayThickness);
	roomY = caseDepth - (2 * inlayThickness);
	
	difference(){
		translate([-0.5, -0.5, -1]) {
			cube([caseWidth+1, caseDepth+1, inlayHighness + 1]);
		}

		translate([inlayThickness, inlayThickness, -1.5]) {
			cube([roomX, roomY, (inlayHighness + 1 + 1)]);
		}
	}
}

module topCase() {
	difference() {
		case();

		positionedMidiPanel();

		translate([25, 35, 20]){
			ledBoard();
		}

		translate([25, 15, 27.5]){
			button();
		}

		translate([95, 15, 27.5]){
			button();
		}

		translate([50, 15, 20]) {
			poti();
		}

		translate([70, 15, 20]) {
			poti();
		}
	}
}

module case() {
	roomX = caseWidth - (2 * wallThickness);
	roomY = caseDepth - (2 * wallThickness);
	roomZ = caseHeight;

	inlayX = caseWidth - (2 * inlayThickness);
	inlayY = caseDepth - (2 * inlayThickness);
	inlayZ = inlayHighness;

	difference() {
		cube([caseWidth, caseDepth, caseHeight]);

		translate([wallThickness, wallThickness, -wallThickness]) {
			cube([roomX, roomY, roomZ]);
		}

		translate([inlayThickness, inlayThickness, -1]) {
			cube([inlayX, inlayY, (inlayZ + 1)]);
		}
	}
}

module positionedMidiPanel() {
	midiPanelWidth = 2 * midiX + midiDistance + 2 * printerTolerance;
	xOffset = (caseWidth - midiPanelWidth) / 2;
	yOffset = caseDepth - wallThickness - 0.5;
	
	translate([xOffset, yOffset, -1]) {
		midiPanel();
	}
}

module midiPanel() {
	midi();

	distance = midiX + midiDistance + printerTolerance;

	translate([distance, 0, 0]) {
		midi();
	}
}

module midi() {
	height = caseHeight - wallThickness + 1;
	y = wallThickness + 1;
	cube( size=[(midiX + printerTolerance), y, height]);
}

module button() {
	cube( (buttonXY + printerTolerance), center=true);
}

module poti() {
	cylinder(h=15, r=(potiRadius + printerTolerance) );
}

module ledBoard() {
	for (i=[0: 10: 70]) {
		translate([i, 0, 0]) {
			led();
		}
	}
}

module led() {
	cylinder(h=15, r=(ledRadius + printerTolerance) );
}


