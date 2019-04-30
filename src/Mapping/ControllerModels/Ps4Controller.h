#include <Controller.h>
#include <Constants.h>

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

	ps4_controller_t() {
		type = PS4;

		X = false;
		CIRCLE = false;
		TRIANGLE = false;
		SQUARE = false;
		D_UP = false;
		D_DOWN = false;
		D_LEFT = false;
		D_RIGHT = false;
		SELECT = false;
		START = false;
		HOME = false;
		LS_PRESS = false;
		RS_PRESS = false;
		L1 = 0;
		R1 = 0;
		L2 = 0;
		R2 = 0;
		LS_X = 128;
		LS_Y = 128;
		RS_X = 128;
		RS_Y = 128;
	}

		virtual bool snes_combo_pressed() override {
			return HOME && X;
		}

		virtual bool nes_combo_pressed() override {
			return HOME && CIRCLE;
	}

	virtual void print_state() override {
		printf("\n---PS4 Controller State---\n");

		printf("X: %d, Circle: %d, Triangle: %d, Square: %d\n", X, CIRCLE, TRIANGLE, SQUARE);
		printf("D-up: %d, D-down: %d, D-left: %d, D-right: %d\n", D_UP, D_DOWN, D_LEFT, D_RIGHT);
		printf("L2: %d, R2: %d\n", L2, R2);
		printf("L1: %d, R1: %d\n", L1, R1);
		printf("Select: %d, Home: %d, Start: %d\n", SELECT, HOME, START);
		printf("LS-x: %d, LS-y: %d, LS-press: %d\n", LS_X, LS_Y, LS_PRESS);
		printf("RS-x: %d, RS-y: %d, RS-press: %d\n", RS_X, RS_Y, RS_PRESS);
	}

	virtual void read_buttons(button_struct_t button_struct) override {
		switch(button_struct.code) {
			case(PS4_LEFT_Y_AXIS):
				printf("Left Analog Stick Y\n");
				LS_Y = button_struct.value;
				break;
			case(PS4_LEFT_X_AXIS):
				printf("Left Analog Stick X\n");
				LS_X = button_struct.value;
				break;
			case(PS4_RIGHT_Y_AXIS):
				printf("Right Analog Stick Y\n");
				RS_Y = button_struct.value;
				break;
			case(PS4_RIGHT_X_AXIS):
				printf("Right Analog Stick X\n");
				RS_X = button_struct.value;
				break;
			case(PS4_DPAD_X):
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
			case(PS4_DPAD_Y):
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
			case(PS4_BTN_CROSS):
				if (button_struct.value == 0) {
					printf("X released\n");
					X = false;
				}
				else {
					printf("X pressed\n");
					X = true;
				}
				break;
			case(PS4_BTN_CIRCLE):
				if (button_struct.value == 0) {
					printf("Circle released\n");
					CIRCLE = false;
				}
				else {
					printf("Circle pressed\n");
					CIRCLE = true;
				}
				break;
			case(PS4_BTN_SQUARE):
				if (button_struct.value == 0) {
					printf("Square released\n");
					SQUARE = false;
				}
				else {
					printf("Square pressed\n");
					SQUARE = true;
				}
				break;
			case(PS4_BTN_TRIANGLE):
				if (button_struct.value == 0) {
					printf("Triangle released\n");
					TRIANGLE = false;
				}
				else {
					printf("Triangle pressed\n");
					TRIANGLE = true;
				}
				break;
			case(PS4_BTN_L1):
				if (button_struct.value == 0) {
					printf("L1 released\n");
					L1 = false;
				}
				else {
					printf("L1 pressed\n");
					L1 = true;
				}
				break;
			case(PS4_BTN_R1):
				if (button_struct.value == 0) {
					printf("R1 released\n");
					R1 = false;
				}
				else {
					printf("R1 pressed\n");
					R1 = true;
				}
				break;
			case(PS4_BTN_START):
				if (button_struct.value == 0) {
					printf("Start released\n");
					START = false;
				}
				else {
					printf("Start pressed\n");
					START = true;
				}
				break;
			case(PS4_BTN_SELECT):
				if (button_struct.value == 0) {
					printf("Select released\n");
					SELECT = false;
				}
				else {
					printf("Select pressed\n");
					SELECT = true;
				}
				break;
			case(PS4_BTN_LS):
				if (button_struct.value == 0) {
					printf("Left Thumb released\n");
					LS_PRESS = false;
				}
				else {
					printf("Left Thumb pressed\n");
					LS_PRESS = true;
				}
				break;
			case(PS4_BTN_RS):
				if (button_struct.value == 0) {
					printf("Right Thumb released\n");
					RS_PRESS = false;
				}
				else {
					printf("Right Thumb pressed\n");
					RS_PRESS = true;
				}
				break;
			case(PS4_BTN_HOME):
				if (button_struct.value == 0) {
					printf("Home released\n");
					HOME = false;
				}
				else {
					printf("Home pressed\n");
					HOME = true;
				}
				break;
			case(PS4_RIGHT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Right Trigger released\n");
				}
				else {
					printf("Right Trigger pressed\n");
				}
				R2 = button_struct.value;
				break;
			case(PS4_LEFT_TRIGGER):
				if (button_struct.value == 0) {
					printf("Left Trigger released\n");
				}
				else {
					printf("Left Trigger pressed\n");
				}
				L2 = button_struct.value;
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
};

#endif
