#include <Constants.h>

#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

struct xbox_controller_t: controller_t {

	const int MAX_AXIS_VALUE = 65535;
	const int STICK_DEADZONE = 10000;
	const int TRIGGER_DEADZONE = 100;

	enum ANALOG_BUTTON {
		LS_UP,
		LS_DOWN,
		LS_LEFT,
		LS_RIGHT,
		RS_UP,
		RS_DOWN,
		RS_LEFT,
		RS_RIGHT,
		LT,
		RT	
	};

	enum DPAD_DIRECTION {
		NONE,
		XB1_DPAD_N,
		XB1_DPAD_NE,
		XB1_DPAD_E,
		XB1_DPAD_SE,
		XB1_DPAD_S,
		XB1_DPAD_SW,
		XB1_DPAD_W,
		XB1_DPAD_NW
	};
	
	const std::map<std::string, ANALOG_BUTTON> string_to_button = {
		{"LS_UP", LS_UP},
		{"LS_DOWN", LS_DOWN},
		{"LS_LEFT", LS_LEFT},
		{"LS_RIGHT", LS_RIGHT},
		{"RS_UP", RS_UP},
		{"RS_DOWN", RS_DOWN},
		{"RS_LEFT", RS_LEFT},
		{"RS_RIGHT", RS_RIGHT},
		{"LT", LT},
		{"RT", RT}
	};
	
	xbox_controller_t() {
		type = XB1;

		//Note: these strings must be exactly the ones used in config files
		button_states["A"] = 0;
		button_states["B"] = 0;
		button_states["X"] = 0;
		button_states["Y"] = 0;
		button_states["D_UP"] = 0;
		button_states["D_DOWN"] = 0;
		button_states["D_LEFT"] = 0;
		button_states["D_RIGHT"] = 0;
		button_states["SELECT"] = 0;
		button_states["START"] = 0;
		button_states["HOME"] = 0;
		button_states["LB"] = 0;
		button_states["RB"] = 0;
		button_states["LS_PRESS"] = 0;
		button_states["RS_PRESS"] = 0;
		button_states["RT"] = 0;
		button_states["LT"] = 0;
		button_states["LS_X"] = 32768;
		button_states["LS_Y"] = 32768;
		button_states["RS_X"] = 32768;
	}

	virtual int combo_pressed() override {
		if (button_states["HOME"]) {
			if (button_states["A"]) {return SNES;}
			if (button_states["B"]) {return NES;}
			if (button_states["X"]) {return GEN;}
			if (button_states["LB"]) {return ATARI_2600;}
			if (button_states["RB"]) {return ATARI_7800;}
			if (button_states["D_UP"]) {return SMS;}
		}
		return false;
	}

	virtual void print_state() override {
		printf("\n---Xbox Controller State---\n");
		printf("A: %d, B: %d, X: %d, Y: %d\n", button_states["A"], button_states["B"], button_states["X"], button_states["Y"]);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", button_states["D_UP"], button_states["D_DOWN"], button_states["D_LEFT"], button_states["D_RIGHT"]);
		printf("LT: %d, RT: %d\n", button_states["LT"], button_states["RT"]);
		printf("LB: %d, RB: %d\n", button_states["LB"], button_states["RB"]);
		printf("Select: %d, Home: %d, Start: %d\n", button_states["SELECT"], button_states["HOME"], button_states["START"]);
		printf("LS-x: %d, LS-y: %d, LS-press: %d\n", button_states["LS_X"], button_states["LS_Y"], button_states["LS_PRESS"]);
		printf("RS-x: %d, RS-y: %d, RS-press: %d\n\n", button_states["RS_X"], button_states["RS_Y"], button_states["RS_PRESS"]);
	}

	void read_buttons(button_struct_t* button_struct) {
		button_states["LS_X"]     = button_struct->LS_X;
		button_states["LS_Y"]     = button_struct->LS_Y;
		button_states["RS_X"]     = button_struct->RS_X;
		button_states["RS_Y"]     = button_struct->RS_Y;
		button_states["LT"]       = button_struct->LT;
		button_states["RT"]       = button_struct->RT;
		button_states["A"]        = (bool)(button_struct->BUTTON & 1);
		button_states["B"]        = (bool)(button_struct->BUTTON & 2);
		button_states["X"]        = (bool)(button_struct->BUTTON & 4);
		button_states["Y"]        = (bool)(button_struct->BUTTON & 8);
		button_states["LB"]       = (bool)(button_struct->BUTTON & 16);
		button_states["RB"]       = (bool)(button_struct->BUTTON & 32);
		button_states["SELECT"]   = (bool)(button_struct->BUTTON & 64);
		button_states["START"]    = (bool)(button_struct->BUTTON & 128);
		button_states["LS_PRESS"] = button_struct->STICK_BUTTON & 1;
		button_states["RS_PRESS"] = button_struct->STICK_BUTTON & 2;

		switch(button_struct->DPAD) {
			case(XB1_DPAD_N):
				button_states["D_UP"]    = 1;
				button_states["D_DOWN"]  = 0;
				button_states["D_LEFT"]  = 0;
				button_states["D_RIGHT"] = 0;
				break;
			case(XB1_DPAD_NE):
				button_states["D_UP"]    = 1;
				button_states["D_DOWN"]  = 0;
				button_states["D_LEFT"]  = 0;
				button_states["D_RIGHT"] = 1;
				break;
			case(XB1_DPAD_E):
				button_states["D_UP"]    = 0;
				button_states["D_DOWN"]  = 0;
				button_states["D_LEFT"]  = 0;
				button_states["D_RIGHT"] = 1;
				break;
			case(XB1_DPAD_SE):
				button_states["D_UP"]    = 0;
				button_states["D_DOWN"]  = 1;
				button_states["D_LEFT"]  = 0;
				button_states["D_RIGHT"] = 1;
				break;
			case(XB1_DPAD_S):
				button_states["D_UP"]    = 0;
				button_states["D_DOWN"]  = 1;
				button_states["D_LEFT"]  = 0;
				button_states["D_RIGHT"] = 0;
				break;
			case(XB1_DPAD_SW):
				button_states["D_UP"]    = 0;
				button_states["D_DOWN"]  = 1;
				button_states["D_LEFT"]  = 1;
				button_states["D_RIGHT"] = 0;
				break;
			case(XB1_DPAD_W):
				button_states["D_UP"]    = 0;
				button_states["D_DOWN"]  = 0;
				button_states["D_LEFT"]  = 1;
				button_states["D_RIGHT"] = 0;
				break;
			case(XB1_DPAD_NW):
				button_states["D_UP"]    = 1;
				button_states["D_DOWN"]  = 0;
				button_states["D_LEFT"]  = 1;
				button_states["D_RIGHT"] = 0;
				break;
			default:
				button_states["D_UP"]    = 0;
				button_states["D_DOWN"]  = 0;
				button_states["D_LEFT"]  = 0;
				button_states["D_RIGHT"] = 0;
				break;
		}		
	}


	int get_mapped_button_state(std::string button, std::map<std::string, std::string> user_map) {
		
		std::string button_aliases = user_map[button];
	        size_t pos = 0;
	        std::string token;
		int deadzone, new_button_value;

		//Loop to handle space separated mapping of two buttons to one button
	        while((pos = button_aliases.find(" ")) != std::string::npos) {
	                token = button_aliases.substr(0, pos);

	                //handling for sticks is different for each direction, handling for triggers is unique, all other buttons captured by else
				switch ((string_to_button.find(token))->second) {
					case LS_LEFT:
			                        deadzone = STICK_DEADZONE;
		        	                new_button_value = -(button_states["LS_X"] - MAX_AXIS_VALUE / 2);
		                		break;
					case LS_RIGHT:
		                        	deadzone = STICK_DEADZONE;
			                        new_button_value = button_states["LS_X"] - MAX_AXIS_VALUE / 2;
						break;
					case LS_UP:
		                		deadzone = STICK_DEADZONE;
		                        	new_button_value = -(button_states["LS_Y"] - MAX_AXIS_VALUE / 2);
		                		break;	
					case LS_DOWN:
		                	        deadzone = STICK_DEADZONE;
		                	        new_button_value = button_states["LS_Y"] - MAX_AXIS_VALUE / 2;
		                		break;	
					case RS_LEFT:
		                        	deadzone = STICK_DEADZONE;
		                        	new_button_value = -(button_states["RS_X"] - MAX_AXIS_VALUE / 2);
		                		break;	
					case RS_RIGHT:
		                        	deadzone = STICK_DEADZONE;
		                	        new_button_value = button_states["RS_X"] - MAX_AXIS_VALUE / 2;
			        		break;        
					case RS_UP:
			                        deadzone = STICK_DEADZONE;
			                        new_button_value = -(button_states["RS_Y"] - MAX_AXIS_VALUE / 2);
			        		break;        
					case RS_DOWN:
			                        deadzone = STICK_DEADZONE;
			                        new_button_value = button_states["RS_Y"] - MAX_AXIS_VALUE / 2;
			        		break;        
					case LT:
					case RT:
			                        deadzone = TRIGGER_DEADZONE;
			                        new_button_value = button_states[token];
			        		break;
					default:
			                        deadzone = 1;
			                        new_button_value = button_states[token];
						break;
				}

	            if(new_button_value >= deadzone) {
	                //analog buttons/sticks: activate button if value is greater than deadzone 
                    //digital buttons: activate button if non-zero
	                return 1;
	            }

				//proceed to next alias (for multiple mappings to one button)
	            button_aliases.erase(0, pos + 1);
	        }

	        return 0;
	}
};

#endif
