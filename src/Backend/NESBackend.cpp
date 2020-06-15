#include <stdio.h>
#include <wiringPi.h>
#include <NESBackend.h>
#include <NesController.h>
#include <Constants.h>

namespace nesbackend {

	static nes_controller_t* output_controller;
	
	void update_controller(nes_controller_t* new_controller) {
		output_controller = new_controller;
	}
}
