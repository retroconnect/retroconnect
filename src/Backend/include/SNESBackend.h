#include <SnesController.h>

#ifndef SNES_BACKEND_H
#define SNES_BACKEND_H

class SNESBackend {

	public: 

		snes_controller_t* output_controller;
		bool output[16];
		int count = 0;

		void setup();
		void update_controller (snes_controller_t* new_controller);
		void set_output();
		void clock_isr();
		void latch_isr();
};

#endif
