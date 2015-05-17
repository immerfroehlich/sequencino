$fn = 50;

difference() {
	cube([10,5,3]);

	translate([0.5, 0.5, -0.5]) {
		cube([9, 4, 3]);
	}

	translate([0.25, 0.25, -0.5]) {
		cube([9.5, 4.5, 1]);
	}

	translate([1.5, 3.5, 3]){
		sphere(1);
	}
}
