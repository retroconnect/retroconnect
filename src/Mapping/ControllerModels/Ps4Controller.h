#include <Controller.h>

#ifndef PS4_CONTROLLER_H
#define PS4_CONTROLLER_H


struct ps4_controller_t: controller_t {
    bool X;
    bool CIRCLE;
    bool TRIANGLE;
    bool SQUARE;
    bool D_UP;
	bool D_DOWN;
	bool D_LEFT;
	bool D_RIGHT;
	bool SELECT;
	bool START;
	bool HOME;
	bool LS_PRESS;
	bool RS_PRESS;
	bool L1;
	bool R1;

	int L2;
	int R2;
	int LS_X;
	int LS_Y;
	int RS_X;
	int RS_Y;


};

#endif
