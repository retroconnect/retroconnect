#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <sys/time.h>
#include <map>
#include "Constants.h"

struct button_struct_t {            //15 bytes total
         unsigned short LS_X;        //2 bytes
         unsigned short LS_Y;        //2 bytes
         unsigned short RS_X;        //2 bytes
         unsigned short RS_Y;        //2 bytes
         unsigned short LT;          //2 bytes
         unsigned short RT;          //2 bytes
         unsigned char DPAD;         //1 byte
         unsigned char BUTTON;       //1 byte
         unsigned char STICK_BUTTON; //1 byte
};

struct controller_t {
	ControllerType type;
	std::map<std::string, int> button_states;
	virtual int combo_pressed() = 0;
	virtual void print_state() = 0;
	virtual void read_buttons(button_struct_t*) = 0;
	virtual void send_state(int, unsigned char[]){};
	virtual int get_mapped_button_state(std::string button, std::map<std::string, std::string> user_map) = 0;
};

#endif
