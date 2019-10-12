#include <stdio.h>
#include <wiringPi.h>
#include <SNESBackend.h>
#include <GenController.h>
#include <Constants.h>

namespace genbackend {

	static gen_controller_t* output_controller;
	static bool output[16];

	void update_controller(gen_controller_t* new_controller) {

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
}
