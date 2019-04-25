#include <stdio.h>
#include <wiringPi.h>
#include <NESBackend.h>
#include <NesController.h>
#include <Constants.h>

namespace nesbackend {

static nes_controller_t* output_controller;
static bool output[8];
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

void update_controller(nes_controller_t* new_controller) {

	output_controller = new_controller;

}

void set_output() {

	output[0] = output_controller->A;
	output[1] = output_controller->B;
	output[2] = output_controller->SELECT;
	output[3] = output_controller->START;
	output[4] = output_controller->D_UP;
	output[5] = output_controller->D_DOWN;
	output[6] = output_controller->D_LEFT;
	output[7] = output_controller->D_RIGHT;

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
