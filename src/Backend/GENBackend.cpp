#include <stdio.h>
#include <wiringPi.h>
#include <SNESBackend.h>
#include <GenController.h>
#include <Constants.h>

namespace genbackend {

	static gen_controller_t* output_controller;

	void update_controller(gen_controller_t* new_controller) {
		output_controller = new_controller;
	}
}
