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
};

#endif
