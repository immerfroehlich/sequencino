$fn = 50;

difference() {
	cube([120,50,30]);

	translate([5, 5, -5]) {
		cube([110, 40, 30]);
	}

	translate([2.5, 2.5, -5]) {
		cube([115, 45, 10]);
	}

	translate([25, 35, 20]){
		ledBoard();
	}

	translate([25, 15, 27.5]){
		cube(10, center=true); //Button
	}

	translate([95, 15, 27.5]){
		cube(10, center=true); //Button
	}

	translate([50, 15, 20]) {
		led(); //Poti
	}

	translate([70, 15, 20]) {
		led(); //Poti
	}
}



module ledBoard() {
	for (i=[0: 10: 70]) {
		translate([i, 0, 0]) {
			led();
		}
	}
}

module led() {
	cylinder(15, 2.5, 2.5);
}


