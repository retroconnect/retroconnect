#include <stdio.h>
#include <wiringPi.h>
#include <SNESBackend.h>
#include <SnesController.h>
#include <Constants.h>

namespace snesbackend {

	static snes_controller_t* output_controller;

	void update_controller(snes_controller_t* new_controller) {
		output_controller = new_controller;
	}
}
