#include <stdio.h>
#include <wiringPi.h>
#include <SNESBackend.h>
#include <SnesController.h>
#include <Constants.h>

namespace snesbackend {

static snes_controller_t* output_controller;
static bool output[16];
static int count = 0;

void setup() {

	wiringPiSetup();

	pinMode(DATA, OUTPUT);
	digitalWrite(DATA, HIGH);
	pinMode(CLOCK, INPUT);
	pinMode(LATCH, INPUT);

	wiringPiISR(CLOCK, INT_EDGE_FALLING, clock_isr);
	wiringPiISR(LATCH, INT_EDGE_FALLING, latch_isr);

}

void update_controller(snes_controller_t* new_controller) {

	output_controller = new_controller;

}

void set_output() {

	output[0] = output_controller->button_states["B"];
	output[1] = output_controller->button_states["Y"];
	output[2] = output_controller->button_states["SELECT"];
	output[3] = output_controller->button_states["START"];
	output[4] = output_controller->button_states["D_UP"];
	output[5] = output_controller->button_states["D_DOWN"];
	output[6] = output_controller->button_states["D_LEFT"];
	output[7] = output_controller->button_states["D_RIGHT"];
	output[8] = output_controller->button_states["A"];
	output[9] = output_controller->button_states["X"];
	output[10] = output_controller->button_states["LB"];
	output[11] = output_controller->button_states["RB"];
	output[12] = false;
	output[13] = false;
	output[14] = false;
	output[15] = false;

}

void clock_isr() {
	if (count == 0)
		return;

	digitalWrite(DATA, !output[count]);
	count++;
}

void latch_isr() {
	//if (count > 7) {
	//	printf("count: %d\n", count);
	//}
	count = 0;
	set_output();
	digitalWrite(DATA, !output[count]);
	count++;
}

}
