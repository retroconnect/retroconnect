#include <Controller.h>

#ifndef SNES_CONTROLLER_H
#define SNES_CONTROLLER_H

struct snes_controller_t: controller_t {
	bool A;
	bool B;
	bool X;
	bool Y;
	bool D_UP;
	bool D_DOWN;
	bool D_LEFT;
	bool D_RIGHT;
	bool SELECT;
	bool START;
	bool LB;
	bool RB;

	snes_controller_t() {
		type = SNES;
	}

	void print_state() {
		printf("\n---SNES Controller State---\n");

		printf("A: %d, B: %d, X: %d, Y: %d\n", A, B, X, Y);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", D_UP, D_DOWN, D_LEFT, D_RIGHT);
		printf("LB: %d, RB: %d\n", LB, RB);
		printf("Select: %d, Start: %d\n\n", SELECT, START);
	}
};

#endif
