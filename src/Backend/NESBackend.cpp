#include <stdio.h>
#include <wiringPi.h>
#include <NESBackend.h>
#include <NesController.h>
#include <Constants.h>

namespace nesbackend {

	static nes_controller_t* output_controller;
	static bool output[8];

	void update_controller(nes_controller_t* new_controller) {

		output_controller = new_controller;

	}

	void set_output() {

		output[0] = output_controller->button_states["A"];
		output[1] = output_controller->button_states["B"];
		output[2] = output_controller->button_states["SELECT"];
		output[3] = output_controller->button_states["START"];
		output[4] = output_controller->button_states["D_UP"];
		output[5] = output_controller->button_states["D_DOWN"];
		output[6] = output_controller->button_states["D_LEFT"];
		output[7] = output_controller->button_states["D_RIGHT"];

	}
}
