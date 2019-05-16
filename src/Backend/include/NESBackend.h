#include <NesController.h>

#ifndef NES_BACKEND_H
#define NES_BACKEND_H

namespace nesbackend {

	void setup();
	void update_controller (nes_controller_t* new_controller);
	void set_output();
	void clock_isr();
	void latch_isr();

}

#endif
