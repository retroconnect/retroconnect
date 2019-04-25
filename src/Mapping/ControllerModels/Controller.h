#ifndef CONTROLLER_H
#define CONTROLLER_H

enum ControllerType {UNSET, XB1, PS4, SNES, NES};

struct controller_t {
	ControllerType type;
};

#endif
