#ifndef CONTROLLER_H
#define CONTROLLER_H

enum ControllerType {Unset, XB1, PS4, SNES};

struct controller_t {
	ControllerType type;
};

#endif
