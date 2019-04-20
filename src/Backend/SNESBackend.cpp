#include <wiringPi.h>
#include <SNESBackend.h>
#include <SnesController.h>

void SNESBackend::setup () {

	wiringPiSetup();

	pinMode(DATA, OUTPUT);
	pinMode(CLOCK, INPUT);
	pinMode(LATCH, INPUT);

	wiringPiISR(CLOCK, INT_EDGE_FALLING, clock_isr);
	wiringPiISR(LATCH, INT_EDGE_FALLING, latch_isr);

}

void SNESBackend::update_controller (snes_controller_t* new_controller) {

	output_controller = new_controller;

}

void SNESBackend::set_output () {

	output[0] = output_controller.B;
	output[1] = output_controller.Y;
	output[2] = output_controller.SELECT;
	output[3] = output_controller.START;
	output[4] = output_controller.D_UP;
	output[5] = output_controller.D_DOWN;
	output[6] = output_controller.D_LEFT;
	output[7] = output_controller.D_RIGHT;
	output[8] = output_controller.A;
	output[9] = output_controller.X;
	output[10] = output_controller.LB;
	output[11] = output_controller.RB;
	output[12] = false;
	output[13] = false;
	output[14] = false;
	output[15] = false;

}

void SNESBackend::clock_isr () {

	if (count == 0)
		return;

	digitalWrite(DATA, 1 - output[count]);

	count++;

}

void SNESBackend::latch_isr () {

	count = 0;

	set_output();

	digitalWrite(DATA, 1 - output[count]);

	count++;

}
