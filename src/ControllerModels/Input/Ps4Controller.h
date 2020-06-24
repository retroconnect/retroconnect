#include <Controller.h>
#include <Constants.h>

#ifndef PS4_CONTROLLER_H
#define PS4_CONTROLLER_H

//PS4 Button Mappings
#define PS4_BTN_CROSS		0x130
#define PS4_BTN_CIRCLE		0x131
#define PS4_BTN_SQUARE		0x134
#define PS4_BTN_TRIANGLE	0x133
#define PS4_BTN_L1		0x136
#define PS4_BTN_R1		0x137
#define PS4_BTN_SELECT		0x13A
#define PS4_BTN_START		0x13B
#define PS4_BTN_LS		0x13D
#define PS4_BTN_RS		0x13E
#define PS4_BTN_HOME		0x13C
#define PS4_LEFT_Y_AXIS		0x01
#define PS4_LEFT_X_AXIS		0x00
#define PS4_RIGHT_Y_AXIS	0x04
#define PS4_RIGHT_X_AXIS	0x03
#define PS4_RIGHT_TRIGGER   	0x05
#define PS4_LEFT_TRIGGER    	0x02
#define PS4_DPAD_X		0x10
#define PS4_DPAD_Y		0x11

struct ps4_controller_t: controller_t {

	const int MAX_AXIS_VALUE = 255;
	const int STICK_DEADZONE = 35;
	const int TRIGGER_DEADZONE = 10;

	enum ANALOG_BUTTON {
		LS_UP,
		LS_DOWN,
		LS_LEFT,
		LS_RIGHT,
		RS_UP,
		RS_DOWN,
		RS_LEFT,
		RS_RIGHT,
		L2,
		R2	
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
		{"L2", L2},
		{"R2", R2}
	};


	ps4_controller_t() {
		type = PS4;

		//Note: these strings must be exactly the ones used in config files
		button_states["X"] = 0;
		button_states["CIRCLE"] = 0;
		button_states["TRIANGLE"] = 0;
		button_states["SQUARE"] = 0;
		button_states["D_UP"] = 0;
		button_states["D_DOWN"] = 0;
		button_states["D_LEFT"] = 0;
		button_states["D_RIGHT"] = 0;
		button_states["SHARE"] = 0;
		button_states["OPTIONS"] = 0;
		button_states["HOME"] = 0;
		button_states["L1"] = 0;
		button_states["R1"] = 0;
		button_states["LS_PRESS"] = 0;
		button_states["RS_PRESS"] = 0;
		button_states["R2"] = 0;
		button_states["L2"] = 0;
		button_states["LS_X"] = 128;
		button_states["LS_Y"] = 128;
		button_states["RS_X"] = 128;
		button_states["RS_Y"] = 128;
	}

	virtual int combo_pressed() override {
		if (button_states["HOME"]) {
			if (button_states["X"]) {return SNES;}
		  	if (button_states["CIRCLE"]) {return NES;}
			if (button_states["SQUARE"]) {return GEN;}	
			if (button_states["L1"]) {return ATARI_2600;}
			if (button_states["R1"]) {return ATARI_7800;}
			if (button_states["D_UP"]) {return SMS;}
		}
		return false;
	}

	virtual void print_state() override {
		printf("\n---PS4 Controller State---\n");
		printf("X: %d, Circle: %d, Triangle: %d, Square: %d\n", button_states["X"], button_states["CIRCLE"], button_states["TRIANGLE"], button_states["SQUARE"]);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", button_states["D_UP"], button_states["D_DOWN"], button_states["D_LEFT"], button_states["D_RIGHT"]);
		printf("L2: %d, R2: %d\n", button_states["L2"], button_states["R2"]);
		printf("L1: %d, R1: %d\n", button_states["L1"], button_states["R1"]);
		printf("Share: %d, Home: %d, Options: %d\n", button_states["SHARE"], button_states["HOME"], button_states["OPTIONS"]);
		printf("LS-x: %d, LS-y: %d, LS-press: %d\n", button_states["LS_X"], button_states["LS_Y"], button_states["LS_PRESS"]);
		printf("RS-x: %d, RS-y: %d, RS-press: %d\n\n", button_states["RS_X"], button_states["RS_Y"], button_states["RS_PRESS"]);
	}

	virtual void read_buttons(button_struct_t button_struct) {
		switch(button_struct.code) {
			case(PS4_LEFT_Y_AXIS):
				printf("Left Analog Stick Y\n");
				button_states["LS_Y"] = button_struct.value;
				break;
			case(PS4_LEFT_X_AXIS):
				printf("Left Analog Stick X\n");
				button_states["LS_X"] = button_struct.value;
				break;
			case(PS4_RIGHT_Y_AXIS):
				printf("Right Analog Stick Y\n");
				button_states["RS_Y"] = button_struct.value;
				break;
			case(PS4_RIGHT_X_AXIS):
				printf("Right Analog Stick X\n");
				button_states["RS_X"] = button_struct.value;
				break;
			case(PS4_DPAD_X):
				if (button_struct.value == 1) {
					printf("DPAD-Right\n");
					button_states["D_RIGHT"] = 0;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-X Released\n");
					button_states["D_RIGHT"] = 0;
					button_states["D_LEFT"] = 0;
				}
				else {
					printf("DPAD-Left\n");
					button_states["D_LEFT"] = 0;
				}
				break;
			case(PS4_DPAD_Y):
				if (button_struct.value == 1) {
					printf("DPAD-Down\n");
					button_states["D_DOWN"] = 0;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-Y Released\n");
					button_states["D_DOWN"] = 0;
					button_states["D_UP"] = 0;
				}
				else {
					printf("DPAD-Up\n");
					button_states["D_UP"] = 0;
				}
				break;
			case(PS4_BTN_CROSS):
				if (button_struct.value == 0) {
					printf("X released\n");
					 button_states["X"]= 0;
				}
				else {
					printf("X pressed\n");
					 button_states["X"]= 0;
				}
				break;
			case(PS4_BTN_CIRCLE):
				if (button_struct.value == 0) {
					printf("Circle released\n");
					button_states["CIRCLE"] = 0;
				}
				else {
					printf("Circle pressed\n");
					button_states["CIRCLE"] = 0;
				}
				break;
			case(PS4_BTN_SQUARE):
				if (button_struct.value == 0) {
					printf("Square released\n");
					button_states["SQUARE"] = 0;
				}
				else {
					printf("Square pressed\n");
					button_states["SQUARE"] = 0;
				}
				break;
			case(PS4_BTN_TRIANGLE):
				if (button_struct.value == 0) {
					printf("Triangle released\n");
					button_states["TRIANGLE"] = 0;
				}
				else {
					printf("Triangle pressed\n");
					button_states["TRIANGLE"] = 0;
				}
				break;
			case(PS4_BTN_L1):
				if (button_struct.value == 0) {
					printf("L1 released\n");
					button_states["L1"] = 0;
				}
				else {
					printf("L1 pressed\n");
					button_states["L1"] = 0;
				}
				break;
			case(PS4_BTN_R1):
				if (button_struct.value == 0) {
					printf("R1 released\n");
					button_states["R1"] = 0;
				}
				else {
					printf("R1 pressed\n");
					button_states["R1"] = 0;
				}
				break;
			case(PS4_BTN_START):
				if (button_struct.value == 0) {
					printf("Start released\n");
					button_states["OPTIONS"] = 0;
				}
				else {
					printf("Start pressed\n");
					button_states["OPTIONS"] = 0;
				}
				break;
			case(PS4_BTN_SELECT):
				if (button_struct.value == 0) {
					printf("Select released\n");
					button_states["SHARE"] = 0;
				}
				else {
					printf("Select pressed\n");
					button_states["SHARE"] = 0;
				}
				break;
			case(PS4_BTN_LS):
				if (button_struct.value == 0) {
					printf("Left Thumb released\n");
					button_states["LS_PRESS"] = 0;
				}
				else {
					printf("Left Thumb pressed\n");
					button_states["LS_PRESS"] = 0;
				}
				break;
			case(PS4_BTN_RS):
				if (button_struct.value == 0) {
					printf("Right Thumb released\n");
					button_states["RS_PRESS"] = 0;
				}
				else {
					printf("Right Thumb pressed\n");
					button_states["RS_PRESS"] = 0;
				}
				break;
			case(PS4_BTN_HOME):
				if (button_struct.value == 0) {
					printf("Home released\n");
					button_states["HOME"] = 0;
				}
				else {
					printf("Home pressed\n");
					button_states["HOME"] = 0;
				}
				break;
			case(PS4_RIGHT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
				}
				else {
					printf("Right Trigger pressed\n");
				}
				button_states["R2"] = button_struct.value;
				break;
			case(PS4_LEFT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Left Trigger released\n");
				}
				else {
					printf("Left Trigger pressed\n");
				}
				button_states["L2"] = button_struct.value;
				break;

			default:
				printf("!!! Unknown button code: %d !!!\n", button_struct.code);
		}
		// Print full struct for button press debugging
		//printf("\nButton Timestamp: %08X", button_struct.time);
		//printf("\nButton Type: %02X", button_struct.type);
		//printf("\nButton Code: %02X", button_struct.code);
		//printf("\nButton Value: %04x\n", button_struct.value);
	}

	int compileMappingsForButton(std::string button, std::map<std::string, std::string> user_map) {
	        std::string button_aliases = user_map[button];
		size_t pos = 0;
	        std::string token;
		int deadzone, new_button_value;
	
	        while((pos = button_aliases.find(" ")) != std::string::npos) {
	                token = button_aliases.substr(0, pos);

	                //handling for sticks is different for each direction, handling for triggers is unique, all other buttons captured by else
	                switch((string_to_button.find(token))->second) {
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
				case L2:
				case R2:
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
