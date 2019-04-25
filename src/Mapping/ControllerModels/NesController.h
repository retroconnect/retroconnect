#include <Controller.h>

#ifndef NES_CONTROLLER_H
#define NES_CONTROLLER_H

struct nes_controller_t: controller_t {
	bool A;
	bool B;
	bool D_UP;
	bool D_DOWN;
	bool D_LEFT;
	bool D_RIGHT;
	bool SELECT;
	bool START;

	nes_controller_t() {
		type = NES;
	}

	void print_state() {
		printf("\n---NES Controller State---\n");

		printf("A: %d, B: %d\n", A, B);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", D_UP, D_DOWN, D_LEFT, D_RIGHT);
		printf("Select: %d, Start: %d\n\n", SELECT, START);
	}
};

#endif
