
module body() {
difference() { // middle seat hole
difference() { // buttom surface
hull() {
translate([0, 0, 10])cube([30, 15, 2], true);
translate([0, 0, 1])cube([55, 16, 2], true);
}

// steering wheel
r = 155.125;
translate([0, 0, -r+3]) rotate([90, 0, 0])cylinder(20, r, r, true, $fn=200);
//translate([0, 0, -92.9808]) rotate([90, 0, 0])cylinder(20, 97.4808, 97.4808, true, $fn=200);
}

// middle seat hole
translate([0, 0, 5+6.25])cube([20, 11, 10], true);
}
}



module ear(thick)

translate([0, 0, 6.2]) rotate([0, -90, 0])
hull() {
translate([8, 0, 0])cylinder(thick, 4.5, 4.5, true);
translate([1, 0, 0])cube([2, 9, thick-0.5],true);
}


module screws () {
// screw_hole
translate([0, 0, 6.2+8])
rotate([0, 90, 0])
cylinder(100, 2.5/2, 2.5/2, true, $fn=20);

// nut
translate([-(4.3/2+3/2+2.7-0.5), 0, 6.2+8])
rotate([0, -90, 0])
cylinder(3, 4.8/2, 5.2/2, $fn=6);

// head
translate([(4.3/2+3/2+2.7), 0, 6.2+8])
rotate([0, 90, 0])
cylinder(3, 4/2, 4.5/2, $fn=50);
}

difference() {
union() {
body();
// middle ear
ear(2.9);
translate([2.9/2+3/2+2.7, 0, 0])ear(3);
translate([-(2.9/2+3/2+2.7), 0, 0])ear(3);
}
screws();
}