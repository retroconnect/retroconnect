#include <Controller.h>
#include <Constants.h>

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

	xbox_controller_t() {
		type = XB1;
	}

	bool snes_combo_pressed() {
		return HOME && A;
	}

	bool nes_combo_pressed() {
		return HOME && B;
	}

	void print_state() {
		printf("\n---Xbox Controller State---\n");

		printf("A: %d, B: %d, X: %d, Y: %d\n", A, B, X, Y);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", D_UP, D_DOWN, D_LEFT, D_RIGHT);
		printf("LT: %d, RT: %d\n", LT, RT);
		printf("LB: %d, RB: %d\n", LB, RB);
		printf("Select: %d, Home: %d, Start: %d\n", SELECT, HOME, START);
		printf("LS-x: %d, LS-y: %d, LS-press: %d\n", LS_X, LS_Y, LS_PRESS);
		printf("RS-x: %d, RS-y: %d, RS-press: %d\n", RS_X, RS_Y, RS_PRESS);
	}

	void read_buttons(button_struct_t button_struct) {
		switch(button_struct.code) {
			case(XB1_LEFT_Y_AXIS):
				printf("Left Analog Stick Y\n");
				LS_Y = button_struct.value;
				break;
			case(XB1_LEFT_X_AXIS):
				printf("Left Analog Stick X\n");
				LS_X = button_struct.value;
				break;
			case(XB1_RIGHT_Y_AXIS):
				printf("Right Analog Stick Y\n");
				RS_Y = button_struct.value;
				break;
			case(XB1_RIGHT_X_AXIS):
				printf("Right Analog Stick X\n");
				RS_X = button_struct.value;
				break;
			case(XB1_DPAD_X):
				if (button_struct.value == 1) {
					printf("DPAD-Right\n");
					D_RIGHT = true;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-X Released\n");
					D_RIGHT = false;
					D_LEFT = false;
				}
				else {
					printf("DPAD-Left\n");
					D_LEFT = true;
				}
				break;
			case(XB1_DPAD_Y):
				if (button_struct.value == 1) {
					printf("DPAD-Down\n");
					D_DOWN = true;
				}
				else if (button_struct.value == 0) {
					printf("DPAD-Y Released\n");
					D_DOWN = false;
					D_UP = false;
				}
				else {
					printf("DPAD-Up\n");
					D_UP = true;
				}
				break;
			case(XB1_BTN_A):
				if (button_struct.value == 0) {
					printf("A released\n");
					A = false;
				}
				else {
					printf("A pressed\n");
					A = true;
				}
				break;
			case(XB1_BTN_B):
				if (button_struct.value == 0) {
					printf("B released\n");
					B = false;
				}
				else {
					printf("B pressed\n");
					B = true;
				}
				break;
			case(XB1_BTN_X):
				if (button_struct.value == 0) {
					printf("X released\n");
					X = false;
				}
				else {
					printf("X pressed\n");
					X = true;
				}
				break;
			case(XB1_BTN_Y):
				if (button_struct.value == 0) {
					printf("Y released\n");
					Y = false;
				}
				else {
					printf("Y pressed\n");
					Y = true;
				}
				break;
			case(XB1_BTN_LB):
				if (button_struct.value == 0) {
					printf("LB released\n");
					LB = false;
				}
				else {
					printf("LB pressed\n");
					LB = true;
				}
				break;
			case(XB1_BTN_RB):
				if (button_struct.value == 0) {
					printf("RB released\n");
					RB = false;
				}
				else {
					printf("RB pressed\n");
					RB = true;
				}
				break;
			case(XB1_BTN_START):
				if (button_struct.value == 0) {
					printf("Start released\n");
					START = false;
				}
				else {
					printf("Start pressed\n");
					START = true;
				}
				break;
			case(XB1_BTN_SELECT):
				if (button_struct.value == 0) {
					printf("Select released\n");
					SELECT = false;
				}
				else {
					printf("Select pressed\n");
					SELECT = true;
				}
				break;
			case(XB1_BTN_LS):
				if (button_struct.value == 0) {
					printf("Left Thumb released\n");
					LS_PRESS = false;
				}
				else {
					printf("Left Thumb pressed\n");
					LS_PRESS = true;
				}
				break;
			case(XB1_BTN_RS):
				if (button_struct.value == 0) {
					printf("Right Thumb released\n");
					RS_PRESS = false;
				}
				else {
					printf("Right Thumb pressed\n");
					RS_PRESS = true;
				}
				break;
			case(XB1_BTN_HOME):
				if (button_struct.value == 0) {
					printf("Home released\n");
					HOME = false;
				}
				else {
					printf("Home pressed\n");
					HOME = true;
				}
				break;
			case(XB1_RIGHT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
				}
				else {
					printf("Right Trigger pressed\n");
				}
				RT = button_struct.value;
				break;
			case(XB1_LEFT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Left Trigger released\n");
				}
				else {
					printf("Left Trigger pressed\n");
				}
				LT = button_struct.value;
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
};

#endif
