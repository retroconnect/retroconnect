#include <Controller.h>

#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

struct xbox_controller_t: controller_t {
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
	bool HOME;
	bool LS_PRESS;
	bool RS_PRESS;
	bool LB;
	bool RB;

	int LT;
	int RT;
	int LS_X;
	int LS_Y;
	int RS_X;
	int RS_Y; 
};

#endif
