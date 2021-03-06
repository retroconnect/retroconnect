#include <Constants.h>

#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

//Xbox One  Bluetooth Button Definitions
#define XB1_BTN_A		0x130
#define XB1_BTN_B		0x131
#define XB1_BTN_X		0x133
#define XB1_BTN_Y		0x134
#define XB1_BTN_LB		0x136
#define XB1_BTN_RB		0x137
#define XB1_BTN_SELECT		0x9E
#define XB1_BTN_START		0x13B
#define XB1_BTN_LS		0x13D
#define XB1_BTN_RS		0x13E
#define XB1_BTN_HOME		0xAC
#define XB1_LEFT_Y_AXIS		0x01
#define XB1_LEFT_X_AXIS		0x00
#define XB1_RIGHT_Y_AXIS	0x05
#define XB1_RIGHT_X_AXIS	0x02
#define XB1_RIGHT_TRIGGER   	0x09
#define XB1_LEFT_TRIGGER   	0x0A
#define XB1_DPAD_X		0x10
#define XB1_DPAD_Y		0x11

//Xbox One Alternate Bluetooth Button Definitions (reconnected controller)
/*
#define XB1_BTN_A		0x130
#define XB1_BTN_B		0x131
#define XB1_BTN_X		0x132
#define XB1_BTN_Y		0x133
#define XB1_BTN_LB		0x134
#define XB1_BTN_RB		0x135
#define XB1_BTN_SELECT		0x136
#define XB1_BTN_START		0x137
#define XB1_BTN_LS		0x138
#define XB1_BTN_RS		0x139
#define XB1_BTN_HOME		0xAC
#define XB1_RIGHT_TRIGGER	0x09
#define XB1_LEFT_TRIGGER    	0x0A
*/

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

	void read_buttons(button_struct_t button_struct) {
		switch(button_struct.code) {
			case(XB1_LEFT_Y_AXIS):
				printf("Left Analog Stick Y\n");
				button_states["LS_Y"] = button_struct.value;
				break;
			case(XB1_LEFT_X_AXIS):
				printf("Left Analog Stick X\n");
				button_states["LS_X"] = button_struct.value;
				break;
			case(XB1_RIGHT_Y_AXIS):
				printf("Right Analog Stick Y\n");
				button_states["RS_Y"] = button_struct.value;
				break;
			case(XB1_RIGHT_X_AXIS):
				printf("Right Analog Stick X\n");
				button_states["RS_X"] = button_struct.value;
				break;
			case(XB1_DPAD_X):
				if (button_struct.value == 1) {
					printf("DPAD-Right\n");
					button_states["D_RIGHT"] = 1;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-X Released\n");
					button_states["D_RIGHT"] = 0;
					button_states["D_LEFT"] = 0;
				}
				else {
					printf("DPAD-Left\n");
					button_states["D_LEFT"] = 1;
				}
				break;
			case(XB1_DPAD_Y):
				if (button_struct.value == 1) {
					printf("DPAD-Down\n");
					button_states["D_DOWN"] = 1;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-Y Released\n");
					button_states["D_DOWN"] = 0;
					button_states["D_UP"] = 0;
				}
				else {
					printf("DPAD-Up\n");
					button_states["D_UP"] = 1;
				}
				break;
			case(XB1_BTN_A):
				if (button_struct.value == 0) {
					printf("A released\n");
					button_states["A"] = 0;
				}
				else {
					printf("A pressed\n");
					button_states["A"] = 1;
				}
				break;
			case(XB1_BTN_B):
				if (button_struct.value == 0) {
					printf("B released\n");
					button_states["B"] = 0;
				}
				else {
					printf("B pressed\n");
					button_states["B"] = 1;
				}
				break;
			case(XB1_BTN_X):
				if (button_struct.value == 0) {
					printf("X released\n");
					button_states["X"] = 0;
				}
				else {
					printf("X pressed\n");
					button_states["X"] = 1;
				}
				break;
			case(XB1_BTN_Y):
				if (button_struct.value == 0) {
					printf("Y released\n");
					button_states["Y"] = 0;
				}
				else {
					printf("Y pressed\n");
					button_states["Y"] = 1;
				}
				break;
			case(XB1_BTN_LB):
				if (button_struct.value == 0) {
					printf("LB released\n");
					button_states["LB"] = 0;
				}
				else {
					printf("LB pressed\n");
					button_states["LB"] = 1;
				}
				break;
			case(XB1_BTN_RB):
				if (button_struct.value == 0) {
					printf("RB released\n");
					button_states["RB"] = 0;
				}
				else {
					printf("RB pressed\n");
					button_states["RB"] = 1;
				}
				break;
			case(XB1_BTN_START):
				if (button_struct.value == 0) {
					printf("Start released\n");
					button_states["START"] = 0;
				}
				else {
					printf("Start pressed\n");
					button_states["START"] = 1;
				}
				break;
			case(XB1_BTN_SELECT):
				if (button_struct.value == 0) {
					printf("Select released\n");
					button_states["SELECT"] = 0;
				}
				else {
					printf("Select pressed\n");
					button_states["SELECT"] = 1;
				}
				break;
			case(XB1_BTN_LS):
				if (button_struct.value == 0) {
					printf("Left Thumb released\n");
					button_states["LS_PRESS"] = 0;
				}
				else {
					printf("Left Thumb pressed\n");
					button_states["LS_PRESS"] = 1;
				}
				break;
			case(XB1_BTN_RS):
				if (button_struct.value == 0) {
					printf("Right Thumb released\n");
					button_states["RS_PRESS"] = 0;
				}
				else {
					printf("Right Thumb pressed\n");
					button_states["RS_PRESS"] = 1;
				}
				break;
			case(XB1_BTN_HOME):
				if (button_struct.value == 0) {
					printf("Home released\n");
					button_states["HOME"] = 0;
				}
				else {
					printf("Home pressed\n");
					button_states["HOME"] = 1;
				}
				break;
			case(XB1_RIGHT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
				}
				else {
					printf("Right Trigger pressed\n");
				}
				button_states["RT"] = button_struct.value;
				break;
			case(XB1_LEFT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Left Trigger released\n");
				}
				else {
					printf("Left Trigger pressed\n");
				}
				button_states["LT"] = button_struct.value;
				break;
			case(4):
				//Junk value
				break;

			default:
				printf("!!! Unknown button code: %d !!!\n", button_struct.code);
		}

		// Print full struct for button press debugging
		//printf("\nButton Timestamp: %08X", button_struct.time);
		//printf("\nButton Type: %02X", button_struct.type);
		//printf("\nButton Code: %02X", button_struct.code);
		//printf("\nButton Value: %04X\n", button_struct.value);
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
