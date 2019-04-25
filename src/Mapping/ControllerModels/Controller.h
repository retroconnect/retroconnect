#ifndef CONTROLLER_H
#define CONTROLLER_H

enum ControllerType {UNSET, XB1, PS4, SNES, NES};

struct controller_t {
	ControllerType type;

	virtual bool snes_combo_pressed() = 0;
	virtual bool nes_combo_pressed() = 0;

	virtual void print_state() = 0;
	virtual void read_buttons() = 0;
};

struct button_struct_t {       //16 bytes total
	struct timeval time;   //8 bytes
	unsigned short type;   //2 bytes
	unsigned short code;   //2 bytes
	unsigned int value;    //4 bytes
} button_struct;

#endif
