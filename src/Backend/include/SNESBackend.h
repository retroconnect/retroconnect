#include <SnesController.h>

#ifndef SNES_BACKEND_H
#define SNES_BACKEND_H

namespace snesbackend {

	void setup();
	void update_controller (snes_controller_t* new_controller);
	void set_output();
	void clock_isr();
	void latch_isr();

}

#endif
