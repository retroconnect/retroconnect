#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sys/time.h>
#include <map>
#include "Constants.h"

struct button_struct_t {       //16 bytes total
         struct timeval time;   //8 bytes
         unsigned short type;   //2 bytes
         unsigned short code;   //2 bytes
         unsigned int value;    //4 bytes
};

struct controller_t {
	ControllerType type;
	std::map<std::string, int> button_states;
	virtual int combo_pressed() = 0;
	virtual void print_state() = 0;
	virtual void read_buttons(button_struct_t) = 0;
	virtual void send_state(int, unsigned char[]){};
	virtual int get_mapped_button_state(std::string button, std::map<std::string, std::string> user_map) = 0;
};

#endif
